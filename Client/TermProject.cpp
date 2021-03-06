// LabProject07-9-1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

// 네트워크
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#define SERVERIP "127.0.0.1"
//#define SERVERIP "192.168.21.49"
#define SERVERPORT 12050
//

#include "stdafx.h"
#include "TermProject.h"
#include "GameFramework.h"

#define MAX_LOADSTRING 100

HINSTANCE						ghAppInstance;
TCHAR							szTitle[MAX_LOADSTRING];
TCHAR							szWindowClass[MAX_LOADSTRING];

CGameFramework					gGameFramework;

RequestMessage rqTankInfo;

CRITICAL_SECTION csResponseSceneBufferAccess;
CRITICAL_SECTION csRequestTankInfoAccess;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// 소켓 함수 오류 출력 후 종료
void err_quit(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);
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


DWORD WINAPI SendThread(LPVOID arg)
{
	CGameTimer GameTimer;
	SOCKET sock = (SOCKET)arg;

	int retval;
	SOCKADDR_IN serveraddr;
	int addrlen;

	// 게임 타이머 리셋
	GameTimer.Reset();
	GameTimer.Start();

	// 서버 정보 얻기
	addrlen = sizeof(serveraddr);
	getpeername(sock, (SOCKADDR*)&serveraddr, &addrlen);

	// 서버에게 데이터 보내기
	while (1) {
		// 쓰기 완료 대기
		GameTimer.Tick(30.0f);

		EnterCriticalSection(&csRequestTankInfoAccess);

		// 데이터 전송
		send(sock, (const char*)&rqTankInfo, sizeof(RequestMessage), NULL);

		ZeroMemory(&rqTankInfo, sizeof(rqTankInfo));
		
		LeaveCriticalSection(&csRequestTankInfoAccess);
	}

	return 0;
}

DWORD WINAPI RecvThread(LPVOID arg)
{
	CGameTimer GameTimer;
	SOCKET sock = (SOCKET)arg;

	int retval;
	SOCKADDR_IN serveraddr;
	int addrlen;
	ResponseMessage rpSceneInfo;

	// 게임타이머 리셋
	GameTimer.Reset();
	GameTimer.Start();

	// 서버 정보 얻기
	addrlen = sizeof(serveraddr);
	getpeername(sock, (SOCKADDR*)&serveraddr, &addrlen);

	// 서버에게 데이터 받기
	while (1) {
		ZeroMemory(&rpSceneInfo, sizeof(rpSceneInfo));
		retval = recvn(sock, (char*)&rpSceneInfo, sizeof(rpSceneInfo), 0);

		EnterCriticalSection(&csResponseSceneBufferAccess);
		gGameFramework.SetResponseMessage(rpSceneInfo);
		LeaveCriticalSection(&csResponseSceneBufferAccess);
	}

	return 0;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit((char*)"socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	//if (retval == SOCKET_ERROR) err_quit((char*)"connect()");

	// make send thread
	HANDLE hSendThread;

	hSendThread = CreateThread(NULL, 0, SendThread, (LPVOID)sock, 0, NULL);
	if (hSendThread == NULL)
		closesocket(sock);
	else
		CloseHandle(hSendThread);

	// InitCS
	InitializeCriticalSection(&csResponseSceneBufferAccess);
	InitializeCriticalSection(&csRequestTankInfoAccess);

	// make recv thread
	HANDLE hRecvThread;

	hRecvThread = CreateThread(NULL, 0, RecvThread, (LPVOID)sock, 0, NULL);
	if (hRecvThread == NULL)
		closesocket(sock);
	else
		CloseHandle(hRecvThread);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	::LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	::LoadString(hInstance, IDC_TERMPROJECT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow)) return(FALSE);

	hAccelTable = ::LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TERMPROJECT));

	while (1)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
		else
		{
			EnterCriticalSection(&csResponseSceneBufferAccess);
			gGameFramework.ApplySceneInfo();
			LeaveCriticalSection(&csResponseSceneBufferAccess);

			gGameFramework.FrameAdvance();
			
			EnterCriticalSection(&csRequestTankInfoAccess);
			rqTankInfo = gGameFramework.GetRequestMessage();
			LeaveCriticalSection(&csRequestTankInfoAccess);
		}
	}
	gGameFramework.OnDestroy();


	// closesocket()
	closesocket(sock);

	// 윈속 종료
	WSACleanup();

	return((int)msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TERMPROJECT));
	wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_LABPROJECT0791);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = ::LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return ::RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	ghAppInstance = hInstance;

	RECT rc = { 0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT };
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_BORDER;
	AdjustWindowRect(&rc, dwStyle, FALSE);
	HWND hMainWnd = CreateWindow(szWindowClass, szTitle, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);

	if (!hMainWnd) return(FALSE);

	gGameFramework.OnCreate(hInstance, hMainWnd);

	::ShowWindow(hMainWnd, nCmdShow);
	::UpdateWindow(hMainWnd);

	return(TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_SIZE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
	case WM_KEYDOWN:
	case WM_KEYUP:
		gGameFramework.OnProcessingWindowMessage(hWnd, message, wParam, lParam);
		break;
	case WM_CHAR:
		gGameFramework.OnProcessingWindowMessage(hWnd, message, wParam, lParam);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			::DialogBox(ghAppInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			::DestroyWindow(hWnd);
			break;
		default:
			return(::DefWindowProc(hWnd, message, wParam, lParam));
		}
		break;
	case WM_PAINT:
		hdc = ::BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	default:
		return(::DefWindowProc(hWnd, message, wParam, lParam));
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return((INT_PTR)TRUE);
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			::EndDialog(hDlg, LOWORD(wParam));
			return((INT_PTR)TRUE);
		}
		break;
	}
	return((INT_PTR)FALSE);
}
