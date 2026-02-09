#pragma once
#include "Client_Define.h"
#include "CObject.h"

BEGIN(Engine)
class CGameManger;
class CShader;
class CVtxBuffer;
class CTransform;
class CCollider;
END

BEGIN(Client)

class CEnemy : public CObject
{
private:
	CEnemy(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
	~CEnemy() = default;

public:
	HRESULT Initialize();
	//void	Early_Update(float _fTimeDelta);
	void	Update(float _fTimeDelta);
	void	Late_Update(float _fTimeDelta);
	HRESULT Render();

protected:
	CShader*	m_pShader		= { nullptr };
	CVtxBuffer* m_pVertexBuffer = { nullptr };
	CTransform* m_pTransform	= { nullptr };
	CCollider*	m_pCollider		= { nullptr };

public:
	static CEnemy* Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
	void Free() override;
};

END
