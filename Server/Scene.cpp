#include "stdafx.h"
#include "Scene.h"

CScene::CScene() {

}

CScene::~CScene() {

}

void CScene::BuildObjects() {
	
	//m_TankObjects[0].SetChild(pTankModelRed, true);
	m_TankObjects[0].OnInitialize();
	m_TankObjects[0].SetPosition(XMFLOAT3(13.0f, 0.0f, -5.0f));
	m_TankObjects[0].SetScaleVar(1.0f, 1.0f, 1.0f);
	m_TankObjects[0].Rotate(0.0f, 0.0f, 0.0f);
	m_TankObjects[0].SetFriction(40.0f);
	m_TankObjects[0].SetMaxVelocityXZ(12.0f);
	m_TankObjects[0].SetAccelSpeedXZ(70.0f);
	m_TankObjects[0].SetSpeedRotateY(180.0f);


	//m_TankObjects[1].SetChild(pTankModelGreen, true);
	m_TankObjects[1].OnInitialize();
	m_TankObjects[1].SetPosition(XMFLOAT3(-3.0f, 0.0f, 30.0f));
	m_TankObjects[1].SetScaleVar(1.0f, 1.0f, 1.0f);
	m_TankObjects[1].Rotate(0.0f, 180.0f, 0.0f);
	m_TankObjects[1].SetFriction(40.0f);
	m_TankObjects[1].SetMaxVelocityXZ(12.0f);
	m_TankObjects[1].SetAccelSpeedXZ(70.0f);
	m_TankObjects[1].SetSpeedRotateY(180.0f);


	//m_TankObjects[2].SetChild(pTankModelGreen, true);
	m_TankObjects[2].OnInitialize();
	m_TankObjects[2].SetPosition(XMFLOAT3(9.0f, 0.0f, 10.0f));	//위치 임의로 잡음
	m_TankObjects[2].SetScaleVar(1.0f, 1.0f, 1.0f);
	m_TankObjects[2].Rotate(0.0f, 90.0f, 0.0f);					//각도 임의로 잡음
	m_TankObjects[2].SetFriction(40.0f);
	m_TankObjects[2].SetMaxVelocityXZ(12.0f);
	m_TankObjects[2].SetAccelSpeedXZ(70.0f);
	m_TankObjects[2].SetSpeedRotateY(180.0f);

}

void CScene::ReleaseObjects() {

}

void CScene::AnimateObjects(float fTimeElapsed) {
	m_fElapsedTime = fTimeElapsed;
	for (int i = 0; i < m_nGameObjects; ++i) m_ppGameObjects[i]->Animate(fTimeElapsed, NULL);
}

bool CScene::ProcessInput(DWORD dwDirection, bool bIsRotateLeft, bool bIsRotateRight, bool bIsFire, int nTankIndex, float fTimeElapsed)
{

	if (!m_TankObjects[nTankIndex].GetDead())
	{
		if (bIsRotateLeft) m_TankObjects[nTankIndex].Rotate(0.0f, -m_TankObjects[nTankIndex].GetSpeedRotateY() * fTimeElapsed, 0.0f);
		if (bIsRotateRight) m_TankObjects[nTankIndex].Rotate(0.0f, m_TankObjects[nTankIndex].GetSpeedRotateY() * fTimeElapsed, 0.0f);
		//if (bIsFire) m_TankObjects[nTankIndex].FireBullet();
		if (dwDirection) m_TankObjects[nTankIndex].Move(dwDirection, m_TankObjects[nTankIndex].GetAccelSpeedXZ() * fTimeElapsed, true);
	}
	m_TankObjects[nTankIndex].Update(fTimeElapsed);

	return(true);
}