#pragma once

#define FRAME_BUFFER_WIDTH		640
#define FRAME_BUFFER_HEIGHT		480

//#include "Timer.h"
//#include "Scene.h"

#pragma pack(1)		// 구조체 멤버 맞춤은 1바이트 경계
struct ResponseMessage
{
	XMFLOAT2 xmf2TankPosition[3];
	XMFLOAT2 xmf2TankLook[3];
	XMFLOAT2 xmf2TankVelocity[3];

	int nPlayerHP[3];
	int nPlayerScore[3];

	bool bBulletsActive[30];
	XMFLOAT2 xmf2BulletsPosition[30];
	XMFLOAT2 xmf2BulletsLook[30];

	bool bItemsActive[6];
	XMFLOAT3 xmf3ItemsPosition[6];

	int nCurrentRound;

	bool bIsGameOver;
};

class CGameFramework
{
public:
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

    void BuildObjects();
    void ReleaseObjects();

    void AnimateObjects();
    void FrameAdvance();

	void CheckGameOver();

private:
	HINSTANCE					m_hInstance;
	HWND						m_hWnd; 

	int							m_nWndClientWidth;
	int							m_nWndClientHeight;

	//CGameTimer					m_GameTimer;

	//CScene						*m_pScene = NULL;

	_TCHAR						m_pszFrameRate[70];

	struct ResponseMessage		m_message;
};

