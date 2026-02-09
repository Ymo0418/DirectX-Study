#pragma once
#include "Client_Define.h"
#include "CBase.h"

BEGIN(Engine)
class CGameManger;
END

BEGIN(Client)

class CMainApp final : public CBase
{
private:
	CMainApp();
	virtual ~CMainApp() = default;

public:
	HRESULT Initialize();
	void Update(float _fTimeDelta);
	void Render();

private:
	CGameManger*			m_pGameManager	= { nullptr };
	ID3D11Device*			m_pDevice		= { nullptr };
	ID3D11DeviceContext*	m_pContext		= { nullptr };

public:
	static CMainApp* Create();
	void Free();
};

END