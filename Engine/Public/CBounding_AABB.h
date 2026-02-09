#pragma once
#include "CBounding.h"

BEGIN(Engine)

class CBounding_AABB final : public CBounding
{
public:
	struct AABB_DESC : public BOUND_DESC {
		XMFLOAT3 vScale;
	};

protected:
	CBounding_AABB();
	virtual ~CBounding_AABB() = default;

public:
	virtual HRESULT Initialize(const BOUND_DESC* _pDesc) override;	
	virtual void	Update(XMMATRIX _matWorld) override;
	virtual bool	IsCollide(CBounding* _pTarget) override;
	const BoundingBox* Get_BoundingBox() {
		return m_pBoundDesc;
	}
#ifdef _DEBUG
	virtual HRESULT Render(PrimitiveBatch<VertexPositionColor>* _pBatch, XMVECTOR _vColor) override;
#endif // _DEBUG

	BoundingBox* m_pBoundDesc			= { nullptr };
	BoundingBox* m_pBoundDesc_Original	= { nullptr };

public:
	static CBounding_AABB* Create(const BOUND_DESC* _pDesc);
	virtual void Free() override;
};

END