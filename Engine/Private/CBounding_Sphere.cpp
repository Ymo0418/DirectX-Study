#include "CBounding_Sphere.h"
#include "CBounding_AABB.h"
#include "CBounding_OBB.h"

CBounding_Sphere::CBounding_Sphere()
{
}

HRESULT CBounding_Sphere::Initialize(const BOUND_DESC* _pDesc)
{
	m_eColType = CCollider::COL_SPHERE;

	const SPHERE_DESC* pDesc = static_cast<const SPHERE_DESC*>(_pDesc);
	m_pBoundDesc = new BoundingSphere(pDesc->vCenter, pDesc->fRadius);

	return S_OK;
}

void CBounding_Sphere::Update(XMMATRIX _matWorld)
{
	m_pBoundDesc->Transform(*m_pBoundDesc, _matWorld);
}

bool CBounding_Sphere::IsCollide(CBounding* _pTarget)
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
HRESULT CBounding_Sphere::Render(PrimitiveBatch<VertexPositionColor>* _pBatch, XMVECTOR _vColor)
{
	DX::Draw(_pBatch, *m_pBoundDesc, _vColor);

	return S_OK;
}
#endif // _DEBUG

CBounding_Sphere* CBounding_Sphere::Create(const BOUND_DESC* _pDesc)
{
	CBounding_Sphere* pInstance = new CBounding_Sphere();

	if (FAILED(pInstance->Initialize(_pDesc)))
	{
		MSG_BOX("Fail Create Sphere");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBounding_Sphere::Free()
{
	Safe_Delete(m_pBoundDesc);
}

