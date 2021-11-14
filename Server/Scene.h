#pragma once

#include "Object.h"

class CScene {
public:
	CScene();
	~CScene();

	void BuildObjects();
	void ReleaseObjects();

	void AnimateObjects(float fTimeElapsed);

public:
	int m_nGameObjects = 0;
	CGameObject** m_ppGameObjects = NULL;

	float m_fElapsedTime = 0.0f;
};