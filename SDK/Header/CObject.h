#pragma once
#include "CBase.h"

BEGIN(Engine)

class MY_DLL CObject abstract: public CBase
{
protected:
	CObject(ID3D11Device * _pDevice, ID3D11DeviceContext * _pContext);
	~CObject() = default;

public:
	virtual HRESULT Initialize() { return S_OK; }
	virtual void	Early_Update(float _fTimeDelta) {}
	virtual void	Update(float _fTimeDelta) {}
	virtual void	Late_Update(float _fTimeDelta) {}
	virtual HRESULT	Render() { return S_OK; }

protected:
	ID3D11Device*			m_pDevice	= { nullptr };
	ID3D11DeviceContext*	m_pContext	= { nullptr };
	class CGameManger*		m_pGameManager = { nullptr };

public:
	void Free() override;
};

END