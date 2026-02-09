#pragma once
#include "CCollider.h"

#ifdef _DEBUG
#include "DebugDraw.h"
#endif // _DEBUG

BEGIN(Engine)

class CBounding abstract : public CBase
{
public:
	struct BOUND_DESC {
		XMFLOAT3 vCenter;
	};

protected:
	CBounding();
	virtual ~CBounding() = default;

public:
	virtual HRESULT		Initialize(const BOUND_DESC* _pDesc) = 0;
	virtual void		Update(XMMATRIX _matWorld) = 0;
	virtual bool		IsCollide(CBounding* _pTarget) = 0;
	CCollider::COL_TYPE Get_Type();
#ifdef _DEBUG
	virtual HRESULT Render(PrimitiveBatch<VertexPositionColor>* _pBatch, XMVECTOR _vColor) = 0;
#endif // _DEBUG

protected:
	CCollider::COL_TYPE m_eColType = { CCollider::COL_END };

public:
	virtual void Free() = 0;
};

END