#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "GameFramework.h"

#define SERVERPORT 12050
#define RECVBUFSIZE	   5

CGameFramework gGameFramework;

HANDLE hRecvThreadEvent[4]; // 0,1,2 : recv ������ �̺�Ʈ, 3 : main ������ �̺�Ʈ
HANDLE hSendBufferWriteEvent;
HANDLE hSendBufferReadEvent;

int recvThreadCnt = 0;	// ������ ��ȣ

// ���� �Լ� ���� ��� �� ����
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

// ���� �Լ� ���� ���
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

// ����� ���� ������ ���� �Լ�
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

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

	// Ŭ���̾�Ʈ�κ��� ������ �ޱ�
	while (1) {
		// ������ ��ȣ ���
		retval = WaitForSingleObject(hRecvThreadEvent[threadID], 3);
		if (retval == WAIT_TIMEOUT) SetEvent(hRecvThreadEvent[threadID + 1]);

		ZeroMemory(&recvbuf, sizeof(recvbuf));

		// ������ ���� �� �� ��ũ�� RequestMessage���ۿ� ����
		retval = recvn(client_sock, recvbuf, RECVBUFSIZE, 0);
		gGameFramework.SetRequestMessage(threadID, recvbuf);
		
		// ���� ���� Ȯ��
		//cout << threadID << endl;
		
		// ���� ������ �̺�Ʈ�� ��ȣ ���·�
		SetEvent(hRecvThreadEvent[threadID + 1]);
	}

	// closesocket()
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	return 0;
}

DWORD WINAPI SendThread(LPVOID arg)
{
	SOCKET* client_socks = (SOCKET*)arg;
	int retval;
	SOCKADDR_IN clientaddrs[3];
	int addrlen[3];

	// Ŭ���̾�Ʈ ���� ���
	for (int i = 0; i < 3; ++i)
	{
		addrlen[i] = sizeof(clientaddrs[i]);
		getpeername(client_socks[i], (SOCKADDR*)&clientaddrs[i], &addrlen[i]);
	}

	// Ŭ���̾�Ʈ�κ��� ������ �ޱ�
	while (1) {
		// ���ӷ����� ���� �Ϸ� ���
		retval = WaitForSingleObject(hSendBufferWriteEvent, INFINITE);
		if (retval == WAIT_TIMEOUT) continue;


		// 3���� Ŭ���̾�Ʈ���� ResponseMessage �۽�
		for (int i = 0; i < 3; ++i)
		{
			retval = send(client_socks[i], (const char*)gGameFramework.GetResponseMessage(), sizeof(ResponseMessage), NULL);
		}
		//ZeroMemory(gGameFramework.GetResponseMessage(), sizeof(ResponseMessage));

		// �б� �Ϸ� �˸�
		SetEvent(hSendBufferReadEvent);
	}

	return 0;
}

int main(int argc, char *argv[]) {
	gGameFramework.BuildObjects();

	int retval;

	// ���� �ʱ�ȭ
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

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKET client_socks[3];
	SOCKADDR_IN clientaddr;
	int addrlen;

	// main ������ �̺�Ʈ ����
	hRecvThreadEvent[3] = CreateEvent(NULL, FALSE, FALSE, NULL);

	// recv ������ ����
	HANDLE hRecvThread[3];

	for (int i = 0; i < 3; ++i) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		client_socks[i] = client_sock;
		// recv ������ ����
		hRecvThread[i] = CreateThread(NULL, 0, RecvThread, (LPVOID)client_sock, 0, NULL);
		if (hRecvThread[i] == NULL)
			closesocket(client_sock);
		else
			CloseHandle(hRecvThread[i]);

		// recv ������ �̺�Ʈ ����
		hRecvThreadEvent[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}
	// send ������ ����
	HANDLE hSendThread;
	hSendThread = CreateThread(NULL, 0, SendThread, (LPVOID)client_socks, 0, NULL);
	if (hSendThread == NULL)
		for (int i = 0; i < 3; ++i) closesocket(client_socks[i]);
	else
		CloseHandle(hSendThread);

	// 0�� ��������� ���� (0 -> 1 -> 2 -> main)
	SetEvent(hRecvThreadEvent[0]);

	while (1) {
		// main ������ ��ȣ ���
		retval = WaitForSingleObject(hRecvThreadEvent[3], 3);
		if (retval == WAIT_TIMEOUT) SetEvent(hRecvThreadEvent[0]);

		gGameFramework.ProcessInput();
		gGameFramework.FrameAdvance();

		retval = WaitForSingleObject(hSendBufferReadEvent, INFINITE);
		gGameFramework.SetResponseMessage();

		// 0�� ������ �̺�Ʈ�� ��ȣ ���·�
		SetEvent(hRecvThreadEvent[0]);
		
		// Send ������ �̺�Ʈ ��ȣ ���·�
		SetEvent(hSendBufferWriteEvent);
	}

	//�̺�Ʈ ����
	CloseHandle(hSendBufferWriteEvent);
	CloseHandle(hSendBufferReadEvent);
	for (int i = 0; i < 4; ++i) {
		CloseHandle(hRecvThreadEvent[i]);
	}

	// closesocket()
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}