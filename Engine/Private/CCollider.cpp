#include "CCollider.h"
#include "CBounding_AABB.h"
#include "CBounding_OBB.h"
#include "CBounding_Sphere.h"

CCollider::CCollider(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
	: m_pDevice{ _pDevice }, m_pContext{ _pContext }
{
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

HRESULT CCollider::Initialize(COL_TYPE _eType, void* _pBoundingDesc)
{
	const CBounding::BOUND_DESC* pDesc = static_cast<const CBounding::BOUND_DESC*>(_pBoundingDesc);

	switch (_eType)
	{
	case CCollider::COL_AABB:
		m_pBounding = CBounding_AABB::Create(pDesc);
		break;
	case CCollider::COL_OBB:
		m_pBounding = CBounding_OBB::Create(pDesc);
		break;
	case CCollider::COL_SPHERE:
		m_pBounding = CBounding_Sphere::Create(pDesc);
		break;
	default:
		break;
	}

#ifdef _DEBUG
	m_pBatch = new PrimitiveBatch<VertexPositionColor>(m_pContext);
	m_pEffect = new BasicEffect(m_pDevice);
	m_pEffect->SetVertexColorEnabled(true);

	const void* pShaderByteCode = { nullptr };
	size_t		iShaderByte = { };

	m_pEffect->GetVertexShaderBytecode(&pShaderByteCode, &iShaderByte);
	m_pDevice->CreateInputLayout(VertexPositionColor::InputElements, VertexPositionColor::InputElementCount, 
								 pShaderByteCode, iShaderByte, &m_pInputLayout);
#endif // _DEBUG

	return S_OK;
}

void CCollider::Update(XMMATRIX _matWorld)
{
	m_pBounding->Update(_matWorld);
}

#ifdef _DEBUG
HRESULT CCollider::Render()
{
	XMFLOAT4X4 view, proj;
	XMMATRIX matView = XMMatrixLookAtLH({ 0.f, 0.f, -5.f, 1.f },
		{ 0.f, 0.f, 0.f, 1.f },
		{ 0.f, 1.f, 0.f, 0.f });
	XMMATRIX matProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.f), 1280.f / 720.f, 0.01f, 1000.f);
	XMStoreFloat4x4(&view, matView);
	XMStoreFloat4x4(&proj, matProj);

	m_pEffect->SetWorld(XMMatrixIdentity());
	m_pEffect->SetView(matView);
	m_pEffect->SetProjection(matProj);

	m_pContext->IASetInputLayout(m_pInputLayout);
	m_pEffect->Apply(m_pContext);
	m_pBatch->Begin();
	
	m_pBounding->Render(m_pBatch, { 0.f, 1.f, 0.f, 1.f });

	m_pBatch->End();

	return S_OK;
}
#endif // _DEBUG

bool CCollider::IsCollide(CCollider* _pTarget)
{
	bool isCollide = m_pBounding->IsCollide(_pTarget->m_pBounding);
	if (isCollide)
	{
		m_tCollisionInfo.pBounding = _pTarget->m_pBounding;
		Safe_AddRef(_pTarget);

		_pTarget->m_tCollisionInfo.pBounding = m_pBounding;
		Safe_AddRef(m_pBounding);
	}

	return isCollide;
}

CCollider::CollisionInfo CCollider::Get_CollisionInfo()
{
	return m_tCollisionInfo;
}

CBounding* CCollider::Get_Bounding()
{
	return m_pBounding;
}

CCollider* CCollider::Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext, COL_TYPE _eType, void* _pBoundingDesc)
{
	CCollider* pInstance = DEB_NEW CCollider(_pDevice, _pContext);

	if (FAILED(pInstance->Initialize(_eType, _pBoundingDesc)))
	{
		MSG_BOX("Fail Create Collider");
		Safe_Release(pInstance);
	}

	return pInstance;

}

void CCollider::Free()
{
	Safe_Release(m_pBounding);
	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
}