#pragma once

#define FRAME_BUFFER_WIDTH		640
#define FRAME_BUFFER_HEIGHT		480

//#include "Timer.h"
//#include "Scene.h"

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
};

