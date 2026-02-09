#pragma once
#include "CBounding.h"

BEGIN(Engine)

class CBounding_Sphere final : public CBounding
{
public:
	struct SPHERE_DESC : public BOUND_DESC {
		float fRadius;
	};

protected:
	CBounding_Sphere();
	virtual ~CBounding_Sphere() = default;

public:
	virtual HRESULT Initialize(const BOUND_DESC* _pDesc) override;	
	virtual void	Update(XMMATRIX _matWorld) override;
	virtual bool	IsCollide(CBounding* _pTarget) override;
	const BoundingSphere* Get_BoundingSphere() {
		return m_pBoundDesc;
	}

#ifdef _DEBUG
	virtual HRESULT Render(PrimitiveBatch<VertexPositionColor>* _pBatch, XMVECTOR _vColor) override;
#endif // _DEBUG

	BoundingSphere* m_pBoundDesc = { nullptr };

public:
	static CBounding_Sphere* Create(const BOUND_DESC* _pDesc);
	virtual void Free() override;
};

END