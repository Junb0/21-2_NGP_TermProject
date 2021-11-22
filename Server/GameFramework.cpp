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
	
	system("cls");
	for (int i = 0; i < 3; ++i) {
		RequestMessage* pTmp = GetRequestMessage(i);
		printf("id: %d, Accel: %d, Deccel: %d, RotateL: %d, RotateR: %d, Fire: %d\n",
			i, pTmp->bIsAccel, pTmp->bIsDeccel, pTmp->bIsRotateLeft, pTmp->bIsRotateRight, pTmp->bIsFire);
	}
	
	//cout << "AnimateObjects ����, fTimeElapsed : " << fTimeElapsed << endl;

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
	//	wstr += L"��������\n";
	//	if(m_pScene->m_ppTankObjects[0]->m_nScore < m_pScene->m_ppTankObjects[1]->m_nScore)
	//		wstr += L"�÷��̾� 1 (�׸�) �¸� \n\n";
	//	else
	//		wstr += L"�÷��̾� 2 (����) �¸� \n\n";
	//	wstr += L"�÷��̾� 1 (�׸�) ����: " + std::to_wstring(int(m_pScene->m_ppTankObjects[1]->m_nScore)) + L" ��\n";
	//	wstr += L"�÷��̾� 2 (����) ����: " + std::to_wstring(int(m_pScene->m_ppTankObjects[0]->m_nScore)) + L" ��\n\n";
	//	wstr += L"�� ���� ��: " + std::to_wstring(m_pScene->m_nNowRound) + L" (3�� ����)\n\n";
	//
	//	LPTSTR s = new TCHAR[wstr.size() + 1];
	//	_tcscpy(s, LPTSTR(wstr.c_str()));
	//	MessageBox(m_hWnd, s, _T("Game Over"), NULL);
	//	PostQuitMessage(0);
	//}
}

void CGameFramework::SetRequestMessage(int id, char* pRecvBuff)
{
	m_RequestMessages[id].bIsAccel = (bool)pRecvBuff[0];
	m_RequestMessages[id].bIsDeccel = (bool)pRecvBuff[1];
	m_RequestMessages[id].bIsRotateLeft = (bool)pRecvBuff[2];
	m_RequestMessages[id].bIsRotateRight = (bool)pRecvBuff[3];
	m_RequestMessages[id].bIsFire = (bool)pRecvBuff[4];
}