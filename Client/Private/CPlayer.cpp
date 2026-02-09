#include "CPlayer.h"
#include "CGameManger.h"
#include "CShader.h"
#include "CVtxBuffer.h"
#include "CTransform.h"
#include "CCollider.h"

CPlayer::CPlayer(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
	: CObject{ _pDevice, _pContext }
{
}

HRESULT CPlayer::Initialize()
{
	m_pShader = CShader::Create(m_pDevice, m_pContext,
		TEXT("../Bin/Hlsl/Squre.hlsl"),
		VtxPosCol::Elements, VtxPosCol::iNumElemet);
	if (!m_pShader)		__debugbreak();

	m_pVertexBuffer = CVtxBuffer::Create(m_pDevice, m_pContext);
	if (!m_pVertexBuffer)		__debugbreak();

	m_pTransform = CTransform::Create(m_pDevice, m_pContext);
	if (!m_pTransform)		__debugbreak();

	CBounding_AABB::AABB_DESC ColDesc{};
	ColDesc.vCenter = { 0.f, 0.f, 0.f };
	ColDesc.vScale = { 0.5f, 0.5f, 0.0001f };
	m_pCollider = CCollider::Create(m_pDevice, m_pContext, CCollider::COL_AABB, &ColDesc);
	if (!m_pCollider)		__debugbreak();

	return S_OK;
}

void CPlayer::Early_Update(float _fTimeDelta)
{
	CCollider::CollisionInfo tColInfo = m_pCollider->Get_CollisionInfo();
	CBounding_AABB* pBounding = static_cast<CBounding_AABB*>(tColInfo.pBounding);
	const BoundingBox* pBoundingBox = pBounding->Get_BoundingBox();

	CBounding_AABB* pMyBounding = static_cast<CBounding_AABB*>(m_pCollider->Get_Bounding());
	const BoundingBox* pMyBoundingBox = pMyBounding->Get_BoundingBox();

	//벽 못지나가는거, Transform Move함수
}

void CPlayer::Update(float _fTimeDelta)
{
	static float x = { 0 };
	static float y = { 0 };
	static float z = { 0 };

	if (m_pGameManager->GetKey(DIK_A))
		x -= 0.001f;
	if (m_pGameManager->GetKey(DIK_D))
		x += 0.001f;

	m_pTransform->Set_Pos({ x,y,z,1.f });
	m_pCollider->Update(m_pTransform->Get_WorldMatrix());
}

void CPlayer::Late_Update(float _fTimeDelta)
{
	m_pGameManager->Add_Collider(CColliderManager::CG_PLAYER, m_pCollider);
}

HRESULT CPlayer::Render()
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

CPlayer* CPlayer::Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
{
	CPlayer* pInstance = new CPlayer(_pDevice, _pContext);

	if (FAILED(pInstance->Initialize()))
	{
		Safe_Release(pInstance);
		__debugbreak();
		return nullptr;
	}

	return pInstance;
}

void CPlayer::Free()
{
	__super::Free();

	Safe_Release(m_pVertexBuffer);
	Safe_Release(m_pShader);
	Safe_Release(m_pCollider);
}