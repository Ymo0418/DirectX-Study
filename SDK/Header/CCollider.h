#pragma once
#include "CBase.h"

BEGIN(Engine)

class MY_DLL CCollider : public CBase
{
public:
	enum COL_TYPE { COL_AABB, COL_OBB, COL_SPHERE, COL_END };

	struct CollisionInfo {
		class CBounding* pBounding = { nullptr };
	};

protected:
	CCollider(ID3D11Device* _pDevice,
				ID3D11DeviceContext* _pContext);
	~CCollider() = default;

public:
	HRESULT Initialize(COL_TYPE _eType, void* _pBoundingDesc);
	void	Update(XMMATRIX _matWorld);
	bool	IsCollide(CCollider* _pTarget);
	CollisionInfo Get_CollisionInfo();
	class CBounding* Get_Bounding();

#ifdef _DEBUG
	HRESULT Render();
#endif // _DEBUG

private:
	class CBounding*		m_pBounding = { nullptr };
	ID3D11Device*			m_pDevice = { nullptr };
	ID3D11DeviceContext*	m_pContext = { nullptr };

	CollisionInfo			m_tCollisionInfo = { };

#ifdef _DEBUG
	PrimitiveBatch<VertexPositionColor>* m_pBatch		= { nullptr };
	BasicEffect*						 m_pEffect		= { nullptr };
	ID3D11InputLayout*					 m_pInputLayout = { nullptr };
#endif // _DEBUG

public:
	static CCollider* Create(ID3D11Device* _pDevice,
							 ID3D11DeviceContext* _pContext, COL_TYPE _eType, void* _pBoundingDesc);
	virtual void Free();
};

END