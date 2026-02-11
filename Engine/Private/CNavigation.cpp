#include "CNavigation.h"

CNavigation::CNavigation(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
	: m_pDevice{ _pDevice }, m_pContext{ _pContext }
{
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

HRESULT CNavigation::Initialize()
{
	LINE* line;

	line = new LINE({ -4, -1 }, { 0, -1 });
	m_Lines.push_back(line);

	line = new LINE({ 0, -1 }, { 1, 0 });
	m_Lines.push_back(line);

	line = new LINE({ 1, 0 }, { 2, -1 });
	m_Lines.push_back(line);

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

	Set_Neighbor();

	return S_OK;
}

float CNavigation::Calc_Height(XMVECTOR vPrePos, XMVECTOR& vMovement)
{
	float NearHeight;	// 제일 가까운 발판
	float NearUndewHeight; // 아래것중에 제일 가까운 발판

	XMVECTOR vPostPos = vPrePos + vMovement;

	if (XMVectorGetX(vPostPos) < m_Lines[m_iCurIdx]->left.x)
	{
		LINE* pLine = m_Lines[m_iCurIdx]->Neighbors[0];
		
		while (nullptr != pLine && 
				false == pLine->IsWithinLine(XMVectorGetX(vPostPos)))
		{
			pLine = pLine->Neighbors[0];
		}

		if (nullptr != pLine) // 찾음
		{
			float h = pLine->Get_Height(vPrePos + vMovement);

			XMVectorSetY(vMovement, -(XMVectorGetY(vPrePos + vMovement) - h));
		}
		else // 못찾음
		{

		}
	}
	else if (m_Lines[m_iCurIdx]->right.x < XMVectorGetX(vPostPos))
	{

	}
	else
	{

	}




	return 0.0f;
}

#ifdef _DEBUG
HRESULT CNavigation::Render()
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

	for (auto* pLine : m_Lines)
	{
		pLine->Render(m_pBatch, { 0, 1, 0, 1 });
	}

	m_pBatch->End();

	return S_OK;
}
#endif // _DEBUG

void CNavigation::Set_Neighbor()
{
	for (LINE* pA : m_Lines)
	{
		for (LINE* pB : m_Lines)
		{
			if (pA == pB)
				continue;

			if (pA->left.x == pB->right.x &&
				pA->left.y == pB->right.y)
			{
				pA->Neighbors[0] = pB;
				pB->Neighbors[1] = pA;
				break;
			}

			if (pA->right.x == pB->left.x &&
				pA->right.y == pB->left.y)
			{
				pA->Neighbors[1] = pB;
				pB->Neighbors[0] = pA;
				break;
			}
		}
	}
}

CNavigation* CNavigation::Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
{
	CNavigation* pInstance = DEB_NEW CNavigation(_pDevice, _pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail Create CNavigation");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CNavigation::Free()
{
	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
}
