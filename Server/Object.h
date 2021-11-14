#pragma once

class CGameObject {
public:
	CGameObject();
	virtual ~CGameObject();

public:
	XMFLOAT4X4 m_xmf4x4Transform;
	XMFLOAT4X4 m_xmf4x4Wrold;

	CGameObject* m_pParent = NULL;
	CGameObject* m_pChild = NULL;
	CGameObject* m_pSibling = NULL;

	BoundingOrientedBox m_xmOOBB;

	bool m_bIsCollisionsPossible = false;
	bool m_bIsItem = false;

	virtual void Animate(float fTimeElapsed, XMFLOAT4X4* pxmf4x4Parent = NULL);

};