#include "CVtxBuffer.h"

CVtxBuffer::CVtxBuffer(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
	: m_pDevice{ _pDevice }, m_pContext{ _pContext }
{
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

HRESULT CVtxBuffer::Initialize()
{
	if (FAILED(Init_VertexBuffer()))
		return E_FAIL;

	if (FAILED(Init_IndexBuffer()))
		return E_FAIL;

	return S_OK;
}

void CVtxBuffer::Update(float _fTimeDelta)
{

}

HRESULT CVtxBuffer::Render()
{
	m_pContext->DrawIndexed(6, 0, 0);

	return S_OK;
}

HRESULT CVtxBuffer::Bind_Resources()
{
	ID3D11Buffer* pVertexBuffers[] = {
		m_pVertexBuffer
	};

	uint VertexStrides[] = {
		sizeof VtxPosCol
	};

	uint Offsets[] = {
		0
	};

	m_pContext->IASetVertexBuffers(0, 1, pVertexBuffers, VertexStrides, Offsets);
	m_pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	m_pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return S_OK;
}

HRESULT CVtxBuffer::Init_VertexBuffer()
{
	ZeroMemory(&m_tBufferDesc, sizeof m_tBufferDesc);
	m_tBufferDesc.ByteWidth = sizeof(VtxPosCol) * 4;
	m_tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_tBufferDesc.CPUAccessFlags = 0;
	m_tBufferDesc.MiscFlags = 0;
	m_tBufferDesc.StructureByteStride = sizeof(VtxPosCol);

	ZeroMemory(&m_tInitialData, sizeof m_tInitialData);
	VtxPosCol vtx[4];
	vtx[0].vPos = XMFLOAT3(-0.5f, 0.5f, 0.f);
	vtx[0].vColor = XMFLOAT3(1.f, 1.f, 1.f);

	vtx[1].vPos = XMFLOAT3(0.5f, 0.5f, 0.f);
	vtx[1].vColor = XMFLOAT3(1.f, 0.f, 1.f);

	vtx[2].vPos = XMFLOAT3(0.5f, -0.5f, 0.f);
	vtx[2].vColor = XMFLOAT3(1.f, 1.f, 1.f);

	vtx[3].vPos = XMFLOAT3(-0.5f, -0.5f, 0.f);
	vtx[3].vColor = XMFLOAT3(1.f, 1.f, 1.f);

	m_tInitialData.pSysMem = vtx;

	if (FAILED(m_pDevice->CreateBuffer(&m_tBufferDesc, &m_tInitialData, &m_pVertexBuffer)))
	{
		__debugbreak();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CVtxBuffer::Init_IndexBuffer()
{
	ZeroMemory(&m_tBufferDesc, sizeof m_tBufferDesc);
	m_tBufferDesc.ByteWidth = sizeof(unsigned short) * 6;
	m_tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_tBufferDesc.CPUAccessFlags = 0;
	m_tBufferDesc.MiscFlags = 0;
	m_tBufferDesc.StructureByteStride = 0;

	ZeroMemory(&m_tInitialData, sizeof m_tInitialData);

	unsigned short idx[6];
	idx[0] = 0;
	idx[1] = 1;
	idx[2] = 2;

	idx[3] = 0;
	idx[4] = 2;
	idx[5] = 3;

	m_tInitialData.pSysMem = idx;

	if (FAILED(m_pDevice->CreateBuffer(&m_tBufferDesc, &m_tInitialData, &m_pIndexBuffer)))
	{
		__debugbreak();
		return E_FAIL;
	}

	return S_OK;
}

CVtxBuffer* CVtxBuffer::Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
{
	CVtxBuffer* pInstance = new CVtxBuffer(_pDevice, _pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail Create VtxBuffer");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVtxBuffer::Free()
{
	__super::Free();

	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
}