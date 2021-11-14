#pragma once

class CScene {
public:
	CScene();
	~CScene();

	void BuildObjects();
	void ReleaseObjects();

	void AnimateObjects(float fTimeElapsed);

public:
};