#include "CBounding_AABB.h"
#include "CBounding_OBB.h"
#include "CBounding_Sphere.h"

CBounding_AABB::CBounding_AABB()
{
}

HRESULT CBounding_AABB::Initialize(const BOUND_DESC* _pDesc)
{
	m_eColType = CCollider::COL_AABB;

	const AABB_DESC* pDesc = static_cast<const AABB_DESC*>(_pDesc);
	m_pBoundDesc_Original = new BoundingBox(pDesc->vCenter, pDesc->vScale);
	m_pBoundDesc = new BoundingBox(*m_pBoundDesc_Original);

	return S_OK;
}

void CBounding_AABB::Update(XMMATRIX _matWorld)
{
	XMMATRIX matWorld = _matWorld;
	matWorld.r[0] = XMVectorSet(1.f, 0.f, 0.f, 0.f) * XMVector3Length(matWorld.r[0]);
	matWorld.r[1] = XMVectorSet(0.f, 1.f, 0.f, 0.f) * XMVector3Length(matWorld.r[1]);
	matWorld.r[2] = XMVectorSet(0.f, 0.f, 1.f, 0.f) * XMVector3Length(matWorld.r[2]);

	m_pBoundDesc_Original->Transform(*m_pBoundDesc, matWorld);
}

bool CBounding_AABB::IsCollide(CBounding* _pTarget)
{
	bool result = { false };

	switch (_pTarget->Get_Type())
	{
	case CCollider::COL_AABB:
		result = m_pBoundDesc->Intersects(*static_cast<CBounding_AABB*>(_pTarget)->Get_BoundingBox());
		break;
	case CCollider::COL_OBB:
		result = m_pBoundDesc->Intersects(*static_cast<CBounding_OBB*>(_pTarget)->Get_BoundingOB());
		break;
	case CCollider::COL_SPHERE:
		result = m_pBoundDesc->Intersects(*static_cast<CBounding_Sphere*>(_pTarget)->Get_BoundingSphere());
		break;
	default:
		break;
	}

	return result;
}

#ifdef _DEBUG
HRESULT CBounding_AABB::Render(PrimitiveBatch<VertexPositionColor>* _pBatch, XMVECTOR _vColor)
{
	DX::Draw(_pBatch, *m_pBoundDesc, _vColor);

	return S_OK;
}
#endif // _DEBUG

CBounding_AABB* CBounding_AABB::Create(const BOUND_DESC* _pDesc)
{
	CBounding_AABB* pInstance = new CBounding_AABB();

	if (FAILED(pInstance->Initialize(_pDesc)))
	{
		MSG_BOX("Fail Create AABB");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBounding_AABB::Free()
{
	Safe_Delete(m_pBoundDesc);
}
