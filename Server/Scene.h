#pragma once

#include "Object.h"

class CScene {
public:
	CScene();
	~CScene();

	void BuildObjects();
	void ReleaseObjects();

	void AnimateObjects(float fTimeElapsed);

	bool ProcessInput(DWORD dwDirection, bool bIsRotateLeft, bool bIsRotateRight, bool bIsFire, int nTankIndex, float fTimeElapsed);

public:
	int m_nGameObjects = 0;
	CGameObject** m_ppGameObjects = NULL;
	CTankObject m_TankObjects[3];

	float m_fElapsedTime = 0.0f;
};