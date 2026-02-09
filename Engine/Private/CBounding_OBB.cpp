#include "CBounding_OBB.h"
#include "CBounding_AABB.h"
#include "CBounding_Sphere.h"

CBounding_OBB::CBounding_OBB()
{
}

HRESULT CBounding_OBB::Initialize(const BOUND_DESC* _pDesc)
{
	m_eColType = CCollider::COL_OBB;

	const OBB_DESC* pDesc = static_cast<const OBB_DESC*>(_pDesc);

	XMFLOAT4 vRot = {};
	XMStoreFloat4(&vRot, XMQuaternionRotationRollPitchYaw(pDesc->vRot.x, 
														  pDesc->vRot.y, 
														  pDesc->vRot.z));
	m_pBoundDesc = new BoundingOrientedBox(pDesc->vCenter, pDesc->vScale, vRot);

	return S_OK;
}

void CBounding_OBB::Update(XMMATRIX _matWorld)
{
	m_pBoundDesc->Transform(*m_pBoundDesc, _matWorld);
}

bool CBounding_OBB::IsCollide(CBounding* _pTarget)
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
HRESULT CBounding_OBB::Render(PrimitiveBatch<VertexPositionColor>* _pBatch, XMVECTOR _vColor)
{
	DX::Draw(_pBatch, *m_pBoundDesc, _vColor);

	return S_OK;
}
#endif // _DEBUG

CBounding_OBB* CBounding_OBB::Create(const BOUND_DESC* _pDesc)
{
	CBounding_OBB* pInstance = new CBounding_OBB();

	if (FAILED(pInstance->Initialize(_pDesc)))
	{
		MSG_BOX("Fail Create OBB");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBounding_OBB::Free()
{
	Safe_Delete(m_pBoundDesc);
}
