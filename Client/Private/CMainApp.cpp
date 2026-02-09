#include "CMainApp.h"
#include "CGameManger.h"
#include "CPlayer.h"
#include "CEnemy.h"

CMainApp::CMainApp()
	: m_pGameManager{ CGameManger::GetInstance() }
{
	Safe_AddRef(m_pGameManager);
}

HRESULT CMainApp::Initialize()
{
	Engine::WND_DESC Desc;
	Desc.hInst = g_hInst;
	Desc.hWnd = g_hWnd;
	Desc.isWindow = true;
	Desc.iWinSizeX = g_iWinSizeX;
	Desc.iWinSizeY = g_iWinSizeY;

	if (FAILED(m_pGameManager->Initialize(Desc, &m_pDevice, &m_pContext)))
		return E_FAIL;

	m_pGameManager->Add_Object(CPlayer::Create(m_pDevice, m_pContext));
	m_pGameManager->Add_Object(CEnemy::Create(m_pDevice, m_pContext));

	return S_OK;
}

void CMainApp::Update(float _fTimeDelta)
{
	m_pGameManager->Update(_fTimeDelta);
}

void CMainApp::Render()
{
	m_pGameManager->Draw();
}

CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp();

	if (FAILED(pInstance->Initialize()))
	{
		if (nullptr == pInstance)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}

	return pInstance;
}


void CMainApp::Free()
{
	Safe_Release(m_pGameManager);
}
