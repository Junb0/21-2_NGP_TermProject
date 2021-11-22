#include "stdafx.h"
#include "Scene.h"

CScene::CScene() {

}

CScene::~CScene() {

}

void CScene::BuildObjects() {

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