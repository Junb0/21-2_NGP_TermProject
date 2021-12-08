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

	void CheckObjectByBulletCollisions();
	void CheckTankObjectByBulletCollisions();
	void CheckTankByObjectCollisions(float fTimeElapsed);

public:
	int m_nGameObjects = 0;
	CGameObject** m_ppGameObjects = NULL;

	int m_nTankObjects = 0;
	CTankObject** m_ppTankObjects = NULL;

	bool m_bIsRoundOver = false;
	bool m_bIsGameOver = false;

	float m_fElapsedTime = 0.0f;
};