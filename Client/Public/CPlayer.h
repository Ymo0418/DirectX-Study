#pragma once
#include "Client_Define.h"
#include "CObject.h"

BEGIN(Engine)
class CGameManger;
class CShader;
class CVtxBuffer;
class CTransform;
class CCollider;
class CNavigation;
END

BEGIN(Client)

class CPlayer : public CObject
{
private:
	CPlayer(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
	~CPlayer() = default;

public:
	HRESULT Initialize();
	void	Early_Update(float _fTimeDelta);
	void	Update(float _fTimeDelta);
	void	Late_Update(float _fTimeDelta);
	HRESULT Render();

protected:
	CShader*	m_pShader		= { nullptr };
	CVtxBuffer*	m_pVertexBuffer = { nullptr };
	CTransform*	m_pTransform	= { nullptr };
	CCollider*	m_pCollider		= { nullptr };
	CNavigation*m_pNavigation	= { nullptr };

	float		m_fJumpingTime = { 0.f };
	bool		m_bJumping = { false };

public:
	static CPlayer* Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
	void Free() override;
};

END