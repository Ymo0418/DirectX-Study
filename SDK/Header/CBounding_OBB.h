#pragma once
#include "CBounding.h"

BEGIN(Engine)

class CBounding_OBB final : public CBounding
{
public:
	struct OBB_DESC : public BOUND_DESC {
		XMFLOAT3 vScale;
		XMFLOAT3 vRot;
	};

protected:
	CBounding_OBB();
	virtual ~CBounding_OBB() = default;

public:
	virtual HRESULT Initialize(const BOUND_DESC* _pDesc) override;	
	virtual void	Update(XMMATRIX _matWorld) override;
	virtual bool	IsCollide(CBounding* _pTarget) override;
	const BoundingOrientedBox* Get_BoundingOB() {
		return m_pBoundDesc;
	}

#ifdef _DEBUG
	virtual HRESULT Render(PrimitiveBatch<VertexPositionColor>* _pBatch, XMVECTOR _vColor) override;
#endif // _DEBUG

	BoundingOrientedBox* m_pBoundDesc = { nullptr };

public:
	static CBounding_OBB* Create(const BOUND_DESC* _pDesc);
	virtual void Free() override;
};

END