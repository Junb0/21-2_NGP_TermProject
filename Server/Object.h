#pragma once

#define DIR_FORWARD					0x01
#define DIR_BACKWARD				0x02
#define DIR_LEFT					0x04
#define DIR_RIGHT					0x08

class CGameObject {
public:
	CGameObject();
	virtual ~CGameObject();

public:
	char m_pstrFrameName[64];

	XMFLOAT4X4 m_xmf4x4Transform;
	XMFLOAT4X4 m_xmf4x4World;

	CGameObject* m_pParent = NULL;
	CGameObject* m_pChild = NULL;
	CGameObject* m_pSibling = NULL;

	BoundingOrientedBox m_xmOOBB;

	bool m_bIsCollisionsPossible = false;
	bool m_bIsItem = false;

	void SetChild(CGameObject* pChild, bool bReferenceUpdate = false);

	XMFLOAT3 GetPosition(){ return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43)); }
	XMFLOAT3 GetLook(){ return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._31, m_xmf4x4World._32, m_xmf4x4World._33))); }
	XMFLOAT3 GetUp(){ return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._21, m_xmf4x4World._22, m_xmf4x4World._23))); }
	XMFLOAT3 GetRight(){ return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._11, m_xmf4x4World._12, m_xmf4x4World._13))); }

	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);
	void SetScale(float x, float y, float z);

	virtual void Animate(float fTimeElapsed, XMFLOAT4X4* pxmf4x4Parent = NULL);

public:
	static CGameObject* LoadFrameHierarchyFromFile(FILE* pInFile);
	static CGameObject* LoadGeometryFromFile(char* pstrFileName);
	static void PrintFrameInfo(CGameObject* pGameObject, CGameObject* pParent);
};

class CBulletObject : public CGameObject
{
public:
	CBulletObject();
	virtual ~CBulletObject();

protected:
	float						m_fSpeed;
	float						m_fBulletEffectiveRange;
	int							m_nDamage;
	float						m_fKnockBackPower;


	XMFLOAT3					m_xmf3FirePosition;

	bool						m_bIsActive;

public:
	void Update(float fTimeElapsed);

	void SetActive(bool bIsActive) { m_bIsActive = bIsActive; }
	void SetFirePosition(XMFLOAT3 xmf3FirePosition);
	void SetDamage(int nDamage) { m_nDamage = nDamage; }
	void SetKnockBackPower(float fKnockBackPower) { m_fKnockBackPower = fKnockBackPower; }

	bool GetActive() { return m_bIsActive; }

	float GetDamage() { return m_nDamage; }
	float GetKnockBackPower() { return m_fKnockBackPower; }
};

class CTankObject : public CGameObject
{
public:
	CTankObject();
	virtual ~CTankObject();

	void BuildBullets(int nBullets = 10);

	void SetFriction(float fFriction) { m_fFriction = fFriction; }
	void SetGravity(const XMFLOAT3& xmf3Gravity) { m_xmf3Gravity = xmf3Gravity; }
	void SetMaxVelocityXZ(float fMaxVelocity) { m_fMaxVelocityXZ = fMaxVelocity; }
	void SetMaxVelocityY(float fMaxVelocity) { m_fMaxVelocityY = fMaxVelocity; }
	void SetVelocity(const XMFLOAT3& xmf3Velocity) { m_xmf3Velocity = xmf3Velocity; }
	void SetPosition(const XMFLOAT3& xmf3Position) { Move(XMFLOAT3(xmf3Position.x - m_xmf3Position.x, xmf3Position.y - m_xmf3Position.y, xmf3Position.z - m_xmf3Position.z), false); }
	void SetAccelSpeedXZ(float fSpeedXZ) { m_fAccelSpeedXZ = fSpeedXZ; }
	void SetSpeedRotateY(float fSpeedRotateY) { m_fSpeedRotateY = fSpeedRotateY; }
	void SetGuaranteeMaxVel(float fBounus) { m_fGuaranteeMaxVelocityXZ = fBounus; }
	void SetGuaranteeFireDelay(float fBonus) { m_fGuaranteeFireDelayTime = fBonus; }

	void SetDead(bool isDead) { m_bIsDead = isDead; }
	bool GetDead() { return m_bIsDead; }

	void SetHP(int nHP) { m_nHP = nHP; }
	int GetHP() { return m_nHP; }

	int m_nScore = 0;
	int m_nBulletDamage = 7;

	XMFLOAT3 GetPosition() { return(m_xmf3Position); }
	XMFLOAT3 GetLookVector() { return(m_xmf3Look); }
	XMFLOAT3 GetUpVector() { return(m_xmf3Up); }
	XMFLOAT3 GetRightVector() { return(m_xmf3Right); }

	XMFLOAT3& GetVelocity() { return(m_xmf3Velocity); }
	float GetYaw() const { return(m_fYaw); }
	float GetPitch() const { return(m_fPitch); }
	float GetRoll() const { return(m_fRoll); }
	float GetAccelSpeedXZ() const { return(m_fAccelSpeedXZ); }
	float GetSpeedRotateY() const { return(m_fSpeedRotateY); }
	float GetGuaranteeMaxVel() { return m_fGuaranteeMaxVelocityXZ; }
	float GetGuaranteeFireDelay() { return m_fGuaranteeFireDelayTime; }

	void SetScaleVar(float x, float y, float z) { m_fScaleX = x;  m_fScaleY = y; m_fScaleZ = z; }

	CGameObject* m_pTankTurret = NULL;
	XMFLOAT4X4 m_xmf4x4OriginalTurretTransform;

protected:

	XMFLOAT3					m_xmf3Position;
	XMFLOAT3					m_xmf3Right;
	XMFLOAT3					m_xmf3Up;
	XMFLOAT3					m_xmf3Look;

	float           			m_fPitch;
	float           			m_fYaw;
	float           			m_fRoll;

	XMFLOAT3					m_xmf3Velocity;
	XMFLOAT3     				m_xmf3Gravity;
	float           			m_fMaxVelocityXZ;
	float						m_fGuaranteeMaxVelocityXZ = 1.0f;
	float           			m_fMaxVelocityY;
	float           			m_fFriction;

	float						m_fScaleX;
	float						m_fScaleY;
	float						m_fScaleZ;

	float						m_fAccelSpeedXZ;
	float						m_fSpeedRotateY;

	float						m_fFireWaitingTime;
	float						m_fFireDelayTime;
	float						m_fGuaranteeFireDelayTime = 1.0f;

	bool						m_bIsDead;
	int							m_nHP;

public:
	int							m_nBullets = 0;
	CBulletObject**				m_ppBullets = NULL;

public:
	virtual void OnInitialize();
	virtual void Animate(float fTimeElapsed, XMFLOAT4X4* pxmf4x4Parent = NULL);

	void Move(DWORD nDirection, float fDistance, bool bVelocity = false);
	void Move(const XMFLOAT3& xmf3Shift, bool bVelocity = false);
	void Rotate(float x, float y, float z);

	void Update(float fTimeElapsed);

};