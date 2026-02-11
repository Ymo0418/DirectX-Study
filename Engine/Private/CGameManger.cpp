#include "CGameManger.h"
#include "CGraphic.h"
#include "CInput.h"
#include "CObjectManager.h"

CGameManger* CGameManger::m_pInstance = nullptr;

CGameManger* CGameManger::GetInstance()
{
	if (nullptr == m_pInstance)
		m_pInstance = new CGameManger;

	return m_pInstance;
}

uint CGameManger::DestroyInstance()
{
	return Safe_Release(m_pInstance);
}

CGameManger::CGameManger()
{

}

HRESULT CGameManger::Initialize(const WND_DESC& _WinDesc, ID3D11Device** _ppDevice, ID3D11DeviceContext** _ppContext)
{
	m_pGraphic = CGraphic::Create(_WinDesc.hWnd, _WinDesc.isWindow, _WinDesc.iWinSizeX, _WinDesc.iWinSizeY, _ppDevice, _ppContext);
	m_pInput = CInput::Create(_WinDesc.hInst, _WinDesc.hWnd);
	m_pObjectManager = CObjectManager::Create();
	m_pColliderManager = CColliderManager::Create();

	return S_OK;
}

void CGameManger::Update(float _fTimeDelta)
{
	m_pInput->Update();

	m_pObjectManager->Early_Update(_fTimeDelta);
	m_pObjectManager->Update(_fTimeDelta);

	m_pColliderManager->Update();

	m_pObjectManager->Late_Update(_fTimeDelta);
}

void CGameManger::Draw()
{
	m_pGraphic->Clear_BackBuffer();
	m_pGraphic->Clear_DepthStencil();

	m_pObjectManager->Render();

	m_pGraphic->Present();
}

bool CGameManger::GetKey(unsigned char _keyID)
{
	return m_pInput->GetKey(_keyID);
}

HRESULT CGameManger::Add_Object(class CObject* _pObj)
{
	m_pObjectManager->Add_Object(_pObj);

	return S_OK;
}

HRESULT	CGameManger::Add_Collider(CColliderManager::COLLIDE_GROUP _eGroup, CCollider* _pCollider)
{
	return m_pColliderManager->Add_Collider(_eGroup, _pCollider);
}

void CGameManger::Free()
{
	Safe_Release(m_pGraphic);
	Safe_Release(m_pInput);
	Safe_Release(m_pObjectManager);
	Safe_Release(m_pColliderManager);
}