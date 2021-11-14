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