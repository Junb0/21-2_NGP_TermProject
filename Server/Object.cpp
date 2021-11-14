#include "stdafx.h"
#include "Object.h"

CGameObject::CGameObject() {
	m_xmf4x4Transform = Matrix4x4::Identity();
	m_xmf4x4Wrold = Matrix4x4::Identity();
}

CGameObject::~CGameObject() {

}

void CGameObject::Animate(float fTimeElapsed, XMFLOAT4X4* pxmf4x4Parent) {
	if (m_pSibling) m_pSibling->Animate(fTimeElapsed, pxmf4x4Parent);
	if (m_pChild) m_pChild->Animate(fTimeElapsed, &m_xmf4x4Wrold);
}