#pragma once
#include "CColliderManager.h"

BEGIN(Engine)

class MY_DLL CGameManger final : public CBase
{
private:
	CGameManger(const CGameManger&) = delete;
	CGameManger& operator = (const CGameManger&) = delete;

private:
	static CGameManger* m_pInstance;

public:
	static CGameManger* GetInstance();
	static uint			DestroyInstance();

private:
	CGameManger();
	virtual ~CGameManger() = default;

public:
	HRESULT Initialize(const WND_DESC& _WinDesc, ID3D11Device** _ppDevice, ID3D11DeviceContext** _ppContext);
	void	Update(float _fTimeDelta);
	void	Draw();

public: /* Input */
	bool	GetKey(unsigned char _keyID);

public: /* Object Manager */
	HRESULT Add_Object(class CObject* _pObj);

public: /* Collider Manager */
	HRESULT	Add_Collider(CColliderManager::COLLIDE_GROUP _eGroup, 
						 CCollider* _pCollider);

private:
	class CGraphic*			m_pGraphic			= { nullptr };
	class CInput*			m_pInput			= { nullptr };
	class CObjectManager*	m_pObjectManager	= { nullptr };
	CColliderManager*		m_pColliderManager	= { nullptr };

public:
	virtual void Free();
};

END