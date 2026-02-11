#include "CShader.h"
#include "CGameManger.h"

CShader::CShader(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
	: m_pDevice{ _pDevice }, m_pContext{ _pContext }, m_pGameManager{CGameManger::GetInstance()}
{
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
	Safe_AddRef(m_pGameManager);
}

HRESULT CShader::Initialize(const wchar_t* _pFilePath, const D3D11_INPUT_ELEMENT_DESC* _Elements, uint _iNumElements)
{
	uint iFlag = 0;

#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	iFlag = D3DCOMPILE_OPTIMIZATION_LEVEL1;
#endif // _DEBUG

	if(FAILED(D3DX11CompileEffectFromFile(_pFilePath, 
										  nullptr, 
										  D3D_COMPILE_STANDARD_FILE_INCLUDE,
										  iFlag,
										  0,
										  m_pDevice,
										  &m_pEffect,
										  nullptr)))
	{
		MSG_BOX("Failed Compile Shader");
		return E_FAIL;
	}


	ID3DX11EffectTechnique* pTechnique = m_pEffect->GetTechniqueByIndex(0);
	
	D3DX11_TECHNIQUE_DESC tDesc{};
	pTechnique->GetDesc(&tDesc);

	ID3D11InputLayout* pLayout;
	ID3DX11EffectPass* pPass = pTechnique->GetPassByIndex(0);

	D3DX11_PASS_DESC tPassDesc{};
	pPass->GetDesc(&tPassDesc);

	if(FAILED(m_pDevice->CreateInputLayout(_Elements, _iNumElements,
										   tPassDesc.pIAInputSignature,
										   tPassDesc.IAInputSignatureSize,
										   &pLayout))) 
		return E_FAIL;

	m_pInputLayout = pLayout;

    return S_OK;
}

HRESULT CShader::Begin()
{
	m_pContext->IASetInputLayout(m_pInputLayout);

	ID3DX11EffectPass* pPass = m_pEffect->GetTechniqueByIndex(0)->GetPassByIndex(0);
	if (!pPass)
	{
		__debugbreak();
		return E_FAIL;
	}

	pPass->Apply(0, m_pContext);

	return S_OK;
}

HRESULT CShader::Bind_Matrix(const char* _pName, const XMFLOAT4X4* _pMatrix)
{
	ID3DX11EffectVariable* pVar = m_pEffect->GetVariableByName(_pName);
	if (!pVar)
	{
		__debugbreak();
		return E_FAIL;
	}

	ID3DX11EffectMatrixVariable* pMatrixVar = pVar->AsMatrix();
	if (!pMatrixVar)
	{
		__debugbreak();
		return E_FAIL;
	}

	HRESULT hr = pMatrixVar->SetMatrix(reinterpret_cast<const float*>(_pMatrix));
	
	return hr;
}

CShader* CShader::Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext, const wchar_t* _pFilePath, const D3D11_INPUT_ELEMENT_DESC* _Elements, uint _iNumElements)
{
	CShader* pInstance = new CShader(_pDevice, _pContext);

	if (FAILED(pInstance->Initialize(_pFilePath, _Elements, _iNumElements)))
	{
		MSG_BOX("Fail Create CShader");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CShader::Free()
{
	__super::Free();

	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
	Safe_Release(m_pGameManager);
}
