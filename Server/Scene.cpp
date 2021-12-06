#include "stdafx.h"
#include "Scene.h"

CScene::CScene() {

}

CScene::~CScene() {

}

void CScene::BuildObjects() {
	
	//CGameObject* pTankModelGreen = CGameObject::LoadGeometryFromFile("Model/GreenTank.bin");
	//CGameObject* pTankModelRed = CGameObject::LoadGeometryFromFile("Model/RedTank.bin");
	
	m_nTankObjects = 3;
	m_ppTankObjects = new CTankObject * [m_nTankObjects];

	CTankObject* pTankObject = NULL;

	pTankObject = new CTankObject();
	//pTankObject->SetChild(pTankModelRed, true);
	pTankObject->OnInitialize();
	pTankObject->SetPosition(XMFLOAT3(13.0f, 0.0f, -5.0f));
	pTankObject->SetScaleVar(1.0f, 1.0f, 1.0f);
	pTankObject->Rotate(0.0f, -90.0f, 0.0f);
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
	//pTankObject->SetChild(pTankModelGreen, true);			
	pTankObject->OnInitialize();
	pTankObject->SetPosition(XMFLOAT3(-15.0f, 0.0f, -3.0f));	
	pTankObject->SetScaleVar(1.0f, 1.0f, 1.0f);
	pTankObject->Rotate(0.0f, 90.0f, 0.0f);					
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
	for (int i = 0; i < m_nTankObjects; ++i) m_ppTankObjects[i]->Animate(fTimeElapsed, NULL);

	if (!m_bIsRoundOver)CheckTankObjectByBulletCollisions();
}

bool CScene::ProcessInput(DWORD dwDirection, bool bIsRotateLeft, bool bIsRotateRight, bool bIsFire, int nTankIndex, float fTimeElapsed)
{

	if (!m_ppTankObjects[nTankIndex]->GetDead())
	{
		if (bIsRotateLeft) m_ppTankObjects[nTankIndex]->Rotate(0.0f, -m_ppTankObjects[nTankIndex]->GetSpeedRotateY() * fTimeElapsed, 0.0f);
		if (bIsRotateRight) m_ppTankObjects[nTankIndex]->Rotate(0.0f, m_ppTankObjects[nTankIndex]->GetSpeedRotateY() * fTimeElapsed, 0.0f);
		if (bIsFire) m_ppTankObjects[nTankIndex]->FireBullet();
		if (dwDirection) m_ppTankObjects[nTankIndex]->Move(dwDirection, m_ppTankObjects[nTankIndex]->GetAccelSpeedXZ() * fTimeElapsed, true);
	}
	m_ppTankObjects[nTankIndex]->Update(fTimeElapsed);

	return(true);
}

void CScene::CheckTankObjectByBulletCollisions()
{
	CBulletObject** ppBullets = NULL;
	for (int i = 0; i < m_nTankObjects; i++)
	{
		ppBullets = m_ppTankObjects[i]->m_ppBullets;
		for (int j = 0; j < m_nTankObjects; j++)
		{
			if (i == j) continue;
			for (int k = 0; k < m_ppTankObjects[i]->m_nBullets; k++)
			{
				if (ppBullets[k]->GetActive())
				{
					if (Vector3::Distance(m_ppTankObjects[j]->GetPosition(), ppBullets[k]->GetPosition()) < 2.0f)
					{
						m_bIsRoundOver = m_ppTankObjects[j]->DamagedByBullet(ppBullets[k]);
						ppBullets[k]->SetActive(false);
					}
				}
			}
		}
	}
}
