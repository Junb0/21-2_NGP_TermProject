#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "GameFramework.h"

#define SERVERPORT 12050
#define RECVBUFSIZE	   5

CGameFramework gGameFramework;

HANDLE hRecvThreadEvent[4]; // 0,1,2 : recv 스레드 이벤트, 3 : main 스레드 이벤트
HANDLE hSendBufferWriteEvent;
HANDLE hSendBufferReadEvent;

int recvThreadCnt = 0;	// 스레드 번호

// 소켓 함수 오류 출력 후 종료
void err_quit(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// 사용자 정의 데이터 수신 함수
int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR) {
			return SOCKET_ERROR;
		}
		else if (received == 0)
			break;

		left -= received;
		ptr += received;
	}

	return len - left;
}


DWORD WINAPI RecvThread(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char recvbuf[RECVBUFSIZE];
	int threadID = recvThreadCnt++;

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

	// 클라이언트로부터 데이터 받기
	while (1) {
		// 스레드 신호 대기
		retval = WaitForSingleObject(hRecvThreadEvent[threadID], 3);
		if (retval == WAIT_TIMEOUT) SetEvent(hRecvThreadEvent[threadID + 1]);

		ZeroMemory(&recvbuf, sizeof(recvbuf));

		// 데이터 수신 및 각 탱크의 RequestMessage버퍼에 저장
		retval = recvn(client_sock, recvbuf, RECVBUFSIZE, 0);
		gGameFramework.SetRequestMessage(threadID, recvbuf);
		
		// 순서 제어 확인
		//cout << threadID << endl;
		
		// 다음 스레드 이벤트를 신호 상태로
		SetEvent(hRecvThreadEvent[threadID + 1]);
	}

	// closesocket()
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	return 0;
}

DWORD WINAPI SendThread(LPVOID arg)
{
	SOCKET* client_socks = (SOCKET*)arg;
	int retval;
	SOCKADDR_IN clientaddrs[3];
	int addrlen[3];

	// 클라이언트 정보 얻기
	for (int i = 0; i < 3; ++i)
	{
		addrlen[i] = sizeof(clientaddrs[i]);
		getpeername(client_socks[i], (SOCKADDR*)&clientaddrs[i], &addrlen[i]);
	}

	// 클라이언트로부터 데이터 받기
	while (1) {
		// 게임루프의 쓰기 완료 대기
		retval = WaitForSingleObject(hSendBufferWriteEvent, INFINITE);
		if (retval == WAIT_TIMEOUT) continue;


		// 3개의 클라이언트에게 ResponseMessage 송신
		for (int i = 0; i < 3; ++i)
		{
			retval = send(client_socks[i], (const char*)gGameFramework.GetResponseMessage(), sizeof(ResponseMessage), NULL);
		}
		//ZeroMemory(gGameFramework.GetResponseMessage(), sizeof(ResponseMessage));

		// 읽기 완료 알림
		SetEvent(hSendBufferReadEvent);
	}

	return 0;
}

int main(int argc, char *argv[]) {
	gGameFramework.BuildObjects();

	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit((char*)"socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit((char*)"bind()");

	//listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	SOCKET client_socks[3];
	SOCKADDR_IN clientaddr;
	int addrlen;

	// main 스레드 이벤트 생성
	hRecvThreadEvent[3] = CreateEvent(NULL, FALSE, FALSE, NULL);

	// recv 스레드 생성
	HANDLE hRecvThread[3];

	for (int i = 0; i < 3; ++i) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// 접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		client_socks[i] = client_sock;
		// recv 스레드 생성
		hRecvThread[i] = CreateThread(NULL, 0, RecvThread, (LPVOID)client_sock, 0, NULL);
		if (hRecvThread[i] == NULL)
			closesocket(client_sock);
		else
			CloseHandle(hRecvThread[i]);

		// recv 스레드 이벤트 생성
		hRecvThreadEvent[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}
	// send 스레드 생성
	HANDLE hSendThread;
	hSendThread = CreateThread(NULL, 0, SendThread, (LPVOID)client_socks, 0, NULL);
	if (hSendThread == NULL)
		for (int i = 0; i < 3; ++i) closesocket(client_socks[i]);
	else
		CloseHandle(hSendThread);

	// 0번 스레드부터 시작 (0 -> 1 -> 2 -> main)
	SetEvent(hRecvThreadEvent[0]);

	while (1) {
		// main 스레드 신호 대기
		retval = WaitForSingleObject(hRecvThreadEvent[3], 3);
		if (retval == WAIT_TIMEOUT) SetEvent(hRecvThreadEvent[0]);

		gGameFramework.ProcessInput();
		gGameFramework.FrameAdvance();

		retval = WaitForSingleObject(hSendBufferReadEvent, INFINITE);
		gGameFramework.SetResponseMessage();

		// 0번 스레드 이벤트를 신호 상태로
		SetEvent(hRecvThreadEvent[0]);
		
		// Send 스레드 이벤트 신호 상태로
		SetEvent(hSendBufferWriteEvent);
	}

	//이벤트 제거
	CloseHandle(hSendBufferWriteEvent);
	CloseHandle(hSendBufferReadEvent);
	for (int i = 0; i < 4; ++i) {
		CloseHandle(hRecvThreadEvent[i]);
	}

	// closesocket()
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}