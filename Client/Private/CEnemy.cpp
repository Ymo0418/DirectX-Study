#include "CEnemy.h"
#include "CGameManger.h"
#include "CShader.h"
#include "CVtxBuffer.h"
#include "CTransform.h"
#include "CCollider.h"

CEnemy::CEnemy(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
	: CObject{ _pDevice, _pContext }
{
}

HRESULT CEnemy::Initialize()
{
	m_pShader = CShader::Create(m_pDevice, m_pContext,
		TEXT("../Bin/Hlsl/Squre.hlsl"),
		VtxPosCol::Elements, VtxPosCol::iNumElemet);
	if (!m_pShader)		__debugbreak();

	m_pVertexBuffer = CVtxBuffer::Create(m_pDevice, m_pContext);
	if (!m_pVertexBuffer)		__debugbreak();

	m_pTransform = CTransform::Create(m_pDevice, m_pContext);
	if (!m_pTransform)		__debugbreak();
	m_pTransform->Set_Pos({ 1.f, 0.f, 0.f, 1.f });
	m_pTransform->Set_Scale({ .5f, .5f, .5f, 1.f });

	CBounding_AABB::AABB_DESC ColDesc{};
	ColDesc.vCenter = { 0.f, 0.f, 0.f };
	ColDesc.vScale = { 0.5f, 0.5f, 0.1f };
	m_pCollider = CCollider::Create(m_pDevice, m_pContext, CCollider::COL_AABB, &ColDesc);
	if (!m_pCollider)		__debugbreak();

	return S_OK;
}

void CEnemy::Update(float _fTimeDelta)
{
	m_pCollider->Update(m_pTransform->Get_WorldMatrix());
}

void CEnemy::Late_Update(float _fTimeDelta)
{
	m_pGameManager->Add_Collider(CColliderManager::CG_ENEMY, m_pCollider);
}

HRESULT CEnemy::Render()
{
	XMFLOAT4X4 view, proj;
	XMMATRIX matView = XMMatrixLookAtLH({ 0.f, 0.f, -5.f, 1.f },
		{ 0.f, 0.f, 0.f, 1.f },
		{ 0.f, 1.f, 0.f, 0.f });
	XMMATRIX matProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.f), 1280.f / 720.f, 0.01f, 1000.f);

	XMStoreFloat4x4(&view, matView);
	XMStoreFloat4x4(&proj, matProj);

	m_pTransform->Bind_Matrix(m_pShader, "WorldMatrix");
	m_pShader->Bind_Matrix("ViewMatrix", &view);
	m_pShader->Bind_Matrix("ProjMatrix", &proj);
	m_pShader->Begin();
	m_pVertexBuffer->Bind_Resources();
	m_pVertexBuffer->Render();

#ifdef _DEBUG
	m_pCollider->Render();
#endif // _DEBUG

	return S_OK;
}

CEnemy* CEnemy::Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
{
	CEnemy* pInstance = new CEnemy(_pDevice, _pContext);

	if (FAILED(pInstance->Initialize()))
	{
		Safe_Release(pInstance);
		__debugbreak();
		return nullptr;
	}

	return pInstance;
}

void CEnemy::Free()
{
	__super::Free();

	Safe_Release(m_pVertexBuffer);
	Safe_Release(m_pShader);
	Safe_Release(m_pCollider);
}