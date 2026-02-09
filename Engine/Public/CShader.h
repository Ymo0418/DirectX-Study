#pragma once
#include "CBase.h"

BEGIN(Engine)

class MY_DLL CShader final : public CBase
{
private:
	CShader(ID3D11Device* _pDevice,
			ID3D11DeviceContext* _pContext);
	~CShader() = default;

public:
	HRESULT Initialize(const wchar_t* _pFilePath, 
					   const D3D11_INPUT_ELEMENT_DESC* _Elements,
					   uint _iNumElements);
	HRESULT Begin();
	HRESULT Bind_Matrix(const char* _pName, const XMFLOAT4X4* _pMatrix);

protected:
	ID3D11Device*				m_pDevice		= { nullptr };
	ID3D11DeviceContext*		m_pContext		= { nullptr };
	class CGameManger*			m_pGameManager	= { nullptr };

private:
	ID3DX11Effect*				m_pEffect		= { nullptr };
	ID3D11InputLayout*			m_pInputLayout	= { nullptr };

public:
	static CShader* Create(ID3D11Device* _pDevice, 
						   ID3D11DeviceContext* _pContext,
						   const wchar_t* _pFilePath,
						   const D3D11_INPUT_ELEMENT_DESC* _Elements,
						   uint _iNumElements);
	virtual void Free() override;
};

END