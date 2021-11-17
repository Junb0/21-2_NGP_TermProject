//-----------------------------------------------------------------------------
// File: CGameFramework.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameFramework.h"

CGameFramework::CGameFramework()
{
	//m_pScene = NULL;
}

CGameFramework::~CGameFramework()
{
}

bool CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	BuildObjects();

	return(true);
}

void CGameFramework::OnDestroy()
{
    ReleaseObjects();
}

void CGameFramework::BuildObjects()
{
	//m_pScene = new CScene();
	//if (m_pScene) m_pScene->BuildObjects();

	m_GameTimer.Reset();
}

void CGameFramework::ReleaseObjects()
{
	//if (m_pScene) m_pScene->ReleaseObjects();
	//if (m_pScene) delete m_pScene;
}

void CGameFramework::AnimateObjects()
{
	float fTimeElapsed = m_GameTimer.GetTimeElapsed();

	//cout << "AnimateObjects 실행, fTimeElapsed : " << fTimeElapsed << endl;

	//if (m_pScene) m_pScene->AnimateObjects(fTimeElapsed);
}

void CGameFramework::FrameAdvance()
{    
	m_GameTimer.Tick(30.0f);
	
    AnimateObjects();

	CheckGameOver();
}

void CGameFramework::CheckGameOver()
{
	//if (m_pScene->m_bIsGameOver) {
	//	std::wstring wstr;
	//	wstr += L"게임종료\n";
	//	if(m_pScene->m_ppTankObjects[0]->m_nScore < m_pScene->m_ppTankObjects[1]->m_nScore)
	//		wstr += L"플레이어 1 (그린) 승리 \n\n";
	//	else
	//		wstr += L"플레이어 2 (레드) 승리 \n\n";
	//	wstr += L"플레이어 1 (그린) 점수: " + std::to_wstring(int(m_pScene->m_ppTankObjects[1]->m_nScore)) + L" 점\n";
	//	wstr += L"플레이어 2 (레드) 점수: " + std::to_wstring(int(m_pScene->m_ppTankObjects[0]->m_nScore)) + L" 점\n\n";
	//	wstr += L"총 라운드 수: " + std::to_wstring(m_pScene->m_nNowRound) + L" (3점 내기)\n\n";
	//
	//	LPTSTR s = new TCHAR[wstr.size() + 1];
	//	_tcscpy(s, LPTSTR(wstr.c_str()));
	//	MessageBox(m_hWnd, s, _T("Game Over"), NULL);
	//	PostQuitMessage(0);
	//}
}