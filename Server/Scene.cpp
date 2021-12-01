#include "stdafx.h"
#include "Scene.h"

CScene::CScene() {

}

CScene::~CScene() {

}

void CScene::BuildObjects() {
	
	//CGameObject* pTankModelGreen = CGameObject::LoadGeometryFromFile("Model/GreenTank.bin");
	//CGameObject* pTankModelRed = CGameObject::LoadGeometryFromFile("Model/RedTank.bin");
	
	m_ppTankObjects = new CTankObject * [3];

	CTankObject* pTankObject = NULL;

	pTankObject = new CTankObject();
	//pTankObject->SetChild(pTankModelRed, true);
	pTankObject->OnInitialize();
	pTankObject->SetPosition(XMFLOAT3(13.0f, 0.0f, -5.0f));
	pTankObject->SetScaleVar(1.0f, 1.0f, 1.0f);
	pTankObject->Rotate(0.0f, 0.0f, 0.0f);
	pTankObject->SetFriction(40.0f);
	pTankObject->SetMaxVelocityXZ(12.0f);
	pTankObject->SetAccelSpeedXZ(70.0f);
	pTankObject->SetSpeedRotateY(180.0f);
	pTankObject->BuildBullets();
	m_ppTankObjects[0] = pTankObject;


	pTankObject = new CTankObject();
	//pTankObject->SetChild(pTankModelGreen, true);
	pTankObject->OnInitialize();
	pTankObject->SetPosition(XMFLOAT3(-3.0f, 0.0f, 30.0f));
	pTankObject->SetScaleVar(1.0f, 1.0f, 1.0f);
	pTankObject->Rotate(0.0f, 180.0f, 0.0f);
	pTankObject->SetFriction(40.0f);
	pTankObject->SetMaxVelocityXZ(12.0f);
	pTankObject->SetAccelSpeedXZ(70.0f);
	pTankObject->SetSpeedRotateY(180.0f);
	pTankObject->BuildBullets();
	m_ppTankObjects[1] = pTankObject;


	pTankObject = new CTankObject();
	//pTankObject->SetChild(pTankModelGreen, true);			// 임의의 모델
	pTankObject->OnInitialize();
	pTankObject->SetPosition(XMFLOAT3(9.0f, 0.0f, 10.0f));	// 임의의 위치
	pTankObject->SetScaleVar(1.0f, 1.0f, 1.0f);
	pTankObject->Rotate(0.0f, 90.0f, 0.0f);					// 임의의 각도
	pTankObject->SetFriction(40.0f);
	pTankObject->SetMaxVelocityXZ(12.0f);
	pTankObject->SetAccelSpeedXZ(70.0f);
	pTankObject->SetSpeedRotateY(180.0f);
	pTankObject->BuildBullets();
	m_ppTankObjects[2] = pTankObject;
	
}

void CScene::ReleaseObjects() {

}

void CScene::AnimateObjects(float fTimeElapsed) {
	m_fElapsedTime = fTimeElapsed;
	for (int i = 0; i < m_nGameObjects; ++i) m_ppGameObjects[i]->Animate(fTimeElapsed, NULL);
	for (int i = 0; i < 3; ++i) m_ppTankObjects[i]->Animate(fTimeElapsed, NULL);
}

bool CScene::ProcessInput(DWORD dwDirection, bool bIsRotateLeft, bool bIsRotateRight, bool bIsFire, int nTankIndex, float fTimeElapsed)
{

	if (!m_ppTankObjects[nTankIndex]->GetDead())
	{
		if (bIsRotateLeft) m_ppTankObjects[nTankIndex]->Rotate(0.0f, -m_ppTankObjects[nTankIndex]->GetSpeedRotateY() * fTimeElapsed, 0.0f);
		if (bIsRotateRight) m_ppTankObjects[nTankIndex]->Rotate(0.0f, m_ppTankObjects[nTankIndex]->GetSpeedRotateY() * fTimeElapsed, 0.0f);
		//if (bIsFire) m_TankObjects[nTankIndex].FireBullet();
		if (dwDirection) m_ppTankObjects[nTankIndex]->Move(dwDirection, m_ppTankObjects[nTankIndex]->GetAccelSpeedXZ() * fTimeElapsed, true);
	}
	m_ppTankObjects[nTankIndex]->Update(fTimeElapsed);

	return(true);
}