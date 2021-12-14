//-----------------------------------------------------------------------------
// File: CGameFramework.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameFramework.h"

CGameFramework::CGameFramework()
{
	m_pScene = NULL;
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
	m_pScene = new CScene();
	if (m_pScene) m_pScene->BuildObjects();



	m_GameTimer.Reset();
}

void CGameFramework::ReleaseObjects()
{
	if (m_pScene) m_pScene->ReleaseObjects();
	if (m_pScene) delete m_pScene;
}

void CGameFramework::AnimateObjects()
{
	float fTimeElapsed = m_GameTimer.GetTimeElapsed();
	//m_ResponseMessage.bIsGameOver = true;

	//system("cls");
	//for (int i = 0; i < 3; ++i) {
	//	RequestMessage* pTmp = GetRequestMessage(i);
	//	printf("id: %d, Accel: %d, Deccel: %d, RotateL: %d, RotateR: %d, Fire: %d\n",
	//		i, pTmp->bIsAccel, pTmp->bIsDeccel, pTmp->bIsRotateLeft, pTmp->bIsRotateRight, pTmp->bIsFire);
	//}
	//cout << "AnimateObjects 실행, fTimeElapsed : " << fTimeElapsed << endl;

	if (m_pScene) m_pScene->AnimateObjects(fTimeElapsed);
}

void CGameFramework::FrameAdvance()
{    
	m_GameTimer.Tick(30.0f);
	
    AnimateObjects();

	//CheckGameOver();
}

void CGameFramework::CheckGameOver()
{
	if (m_pScene->m_bIsGameOver) {
		std::string str;
		str += "게임종료\n";

		int p1Score = m_pScene->m_ppTankObjects[0]->m_nScore;
		int p2Score = m_pScene->m_ppTankObjects[1]->m_nScore;
		int p3Score = m_pScene->m_ppTankObjects[2]->m_nScore;

		if (p1Score > p2Score) {
			if(p1Score > p3Score)
			str += "플레이어1 승리 \n\n";
			else
			str += "플레이어3 승리 \n\n";
		}
		else {
			if(p2Score > p3Score)
			str += "플레이어2 승리 \n\n";
			else
			str += "플레이어3 승리 \n\n";
		}
		str += "플레이어1 점수: " + std::to_string(p1Score) + " 점\n";
		str += "플레이어2 점수: " + std::to_string(p2Score) + " 점\n\n";
		str += "플레이어3 점수: " + std::to_string(p3Score) + " 점\n\n";
		str += "총 라운드 수: " + std::to_string(m_pScene->m_nCurrentRound) + " (3점 내기)\n\n";
	
		printf(str.c_str());
		//PostQuitMessage(0);
	}
}

void CGameFramework::SetRequestMessage(int id, char* pRecvBuff)
{
	m_RequestMessages[id].bIsAccel = (bool)pRecvBuff[0];
	m_RequestMessages[id].bIsDeccel = (bool)pRecvBuff[1];
	m_RequestMessages[id].bIsRotateLeft = (bool)pRecvBuff[2];
	m_RequestMessages[id].bIsRotateRight = (bool)pRecvBuff[3];
	m_RequestMessages[id].bIsFire = (bool)pRecvBuff[4];
}

void CGameFramework::SetResponseMessage()
{
	CTankObject** ppTankObjects = m_pScene->m_ppTankObjects;
	for (int i = 0; i < 3; ++i) {
		m_ResponseMessage.xmf2TankPosition[i] = XMFLOAT2(ppTankObjects[i]->GetPosition().x, ppTankObjects[i]->GetPosition().z);
		m_ResponseMessage.xmf2TankLook[i] = XMFLOAT2(ppTankObjects[i]->GetLookVector().x, ppTankObjects[i]->GetLookVector().z);
		m_ResponseMessage.xmf2TankVelocity[i] = XMFLOAT2(ppTankObjects[i]->GetVelocity().x, ppTankObjects[i]->GetVelocity().z);

		m_ResponseMessage.nPlayerHP[i] = ppTankObjects[i]->GetHP();
		m_ResponseMessage.nPlayerScore[i] = ppTankObjects[i]->m_nScore;

		
		for (int j = 0; j < 10; ++j) {
			m_ResponseMessage.bBulletsActive[i * 10 + j] = ppTankObjects[i]->m_ppBullets[j]->GetActive();
			m_ResponseMessage.xmf2BulletsPosition[i * 10 + j] = XMFLOAT2(ppTankObjects[i]->m_ppBullets[j]->GetPosition().x, ppTankObjects[i]->m_ppBullets[j]->GetPosition().z);
			m_ResponseMessage.xmf2BulletsLook[i * 10 + j] = XMFLOAT2(ppTankObjects[i]->m_ppBullets[j]->GetLook().x, ppTankObjects[i]->m_ppBullets[j]->GetLook().z);
		}
		
	}

	CGameObject** ppGameObjects = m_pScene->m_ppGameObjects;
	for (int i = 0; i < 6; ++i) {
		m_ResponseMessage.bItemsActive[i] = ((CItemObject*)ppGameObjects[i + 106])->m_bIsActive;
		m_ResponseMessage.xmf3ItemsPosition[i] = XMFLOAT3{ ((CItemObject*)ppGameObjects[i + 106])->GetPosition().x, ((CItemObject*)ppGameObjects[i + 106])->GetPosition().y, ((CItemObject*)ppGameObjects[i + 106])->GetPosition().z };
	}
	

	m_ResponseMessage.nCurrentRound = m_pScene->m_nCurrentRound;
	m_ResponseMessage.bIsRoundOver = m_pScene->m_bIsRoundOver;

	m_ResponseMessage.bIsGameOver = m_pScene->m_bIsGameOver;
}

void CGameFramework::ProcessInput()
{
	float fTimeElapsed = m_GameTimer.GetTimeElapsed();
	for (int i = 0; i < 3; ++i)
	{
		DWORD dwDirection = 0;

		if (m_RequestMessages[i].bIsAccel) dwDirection |= DIR_FORWARD;
		if (m_RequestMessages[i].bIsDeccel) dwDirection |= DIR_BACKWARD;

		m_pScene->ProcessInput(dwDirection, m_RequestMessages[i].bIsRotateLeft, m_RequestMessages[i].bIsRotateRight, m_RequestMessages[i].bIsFire, i, fTimeElapsed);
	}
}