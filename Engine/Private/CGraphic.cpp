#include "CGraphic.h"

CGraphic::CGraphic()
{
}

HRESULT CGraphic::Initialize(HWND _hWnd, bool _isWindowed, uint _iWinSizeX, uint _iWinSizeY, _Inout_ ID3D11Device** _ppDevice, _Inout_ ID3D11DeviceContext** _ppContext)
{
	uint iFlag = 0;

	D3D_FEATURE_LEVEL FeatureLV;

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, iFlag, nullptr, 0, D3D11_SDK_VERSION,
		&m_pDevice, &FeatureLV, &m_pContext)))
		return E_FAIL;

	if (FAILED(Ready_SwapChain(_hWnd, _isWindowed, _iWinSizeX, _iWinSizeY)))
		return E_FAIL;

	if (FAILED(Ready_BackBufferRTV()))
		return E_FAIL;

	if (FAILED(Ready_DepthStencilView(_iWinSizeX, _iWinSizeY)))
		return E_FAIL;

	ID3D11RenderTargetView* pRTVs[1] = {
		m_pBackBufferRTV
	};

	m_pContext->OMSetRenderTargets(1, pRTVs, m_pDepthStencilView);

	D3D11_VIEWPORT ViewportDesc;
	ZeroMemory(&ViewportDesc, sizeof ViewportDesc);

	ViewportDesc.TopLeftX = 0;
	ViewportDesc.TopLeftY = 0;
	ViewportDesc.Width = (float)_iWinSizeX;
	ViewportDesc.Height = (float)_iWinSizeY;
	ViewportDesc.MinDepth = 0.f;
	ViewportDesc.MaxDepth = 1.f;

	m_pContext->RSSetViewports(1, &ViewportDesc);

	*_ppContext = m_pContext;
	*_ppDevice = m_pDevice;

	Safe_AddRef(m_pContext);
	Safe_AddRef(m_pDevice);

	return S_OK;
}

HRESULT CGraphic::Present()
{
	return m_pSwapChain->Present(1, 0);
}

HRESULT CGraphic::Clear_BackBuffer()
{
	XMFLOAT4 vColor = { 0.f, 0.f, 1.f, 1.f };	
	m_pContext->ClearRenderTargetView(m_pBackBufferRTV, (float*)&vColor);

	return S_OK;
}

HRESULT CGraphic::Clear_DepthStencil()
{
	m_pContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

	return S_OK;
}

HRESULT CGraphic::Ready_SwapChain(HWND _hWnd, bool _isWindowed, uint _iWinSizeX, uint _iWinSizeY)
{
	IDXGIDevice* pDevice = nullptr;
	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDevice);

	IDXGIAdapter* pAdapter = nullptr;
	pDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pAdapter);

	IDXGIFactory* pFactory = nullptr;
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	DXGI_SWAP_CHAIN_DESC SwapChain;
	ZeroMemory(&SwapChain, sizeof DXGI_SWAP_CHAIN_DESC);

	SwapChain.BufferDesc.Width = _iWinSizeX;
	SwapChain.BufferDesc.Height = _iWinSizeY;
	
	SwapChain.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	SwapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	SwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChain.BufferCount = 1;

	SwapChain.BufferDesc.RefreshRate.Numerator = 60;
	SwapChain.BufferDesc.RefreshRate.Denominator = 1;

	SwapChain.SampleDesc.Quality = 0;
	SwapChain.SampleDesc.Count = 1;

	SwapChain.OutputWindow = _hWnd;
	SwapChain.Windowed = _isWindowed;
	SwapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (FAILED(pFactory->CreateSwapChain(m_pDevice, &SwapChain, &m_pSwapChain)))
	{
		MSG_BOX("Failed : CreateSwapChain");
		return E_FAIL;
	}

	Safe_Release(pFactory);
	Safe_Release(pAdapter);
	Safe_Release(pDevice);

	return S_OK;
}

HRESULT CGraphic::Ready_BackBufferRTV()
{
	ID3D11Texture2D* pBackBufferTexture = nullptr;

	if (FAILED(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBufferTexture)))
		return E_FAIL;

	if (FAILED(m_pDevice->CreateRenderTargetView(pBackBufferTexture, nullptr, &m_pBackBufferRTV)))
		return E_FAIL;

	Safe_Release(pBackBufferTexture);

	return S_OK;
}

HRESULT CGraphic::Ready_DepthStencilView(uint _iWinSizeX, uint _iWinSizeY)
{
	ID3D11Texture2D* pDepthStencilTexture = nullptr;

	D3D11_TEXTURE2D_DESC TextureDesc;
	ZeroMemory(&TextureDesc, sizeof(TextureDesc));

	TextureDesc.Width = _iWinSizeX;
	TextureDesc.Height = _iWinSizeY;
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	
	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.SampleDesc.Count = 1;

	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	if (FAILED(m_pDevice->CreateTexture2D(&TextureDesc, nullptr, &pDepthStencilTexture)))
		return E_FAIL;

	if(FAILED(m_pDevice->CreateDepthStencilView(pDepthStencilTexture, NULL, &m_pDepthStencilView)))
		return E_FAIL;

	return S_OK;
}

CGraphic* CGraphic::Create(HWND _hWnd, bool _isWindowed, uint _iWinSizeX, uint _iWinSizeY, ID3D11Device** _ppDevice, ID3D11DeviceContext** _ppContext)
{
	CGraphic* pInstance = new CGraphic();

	if (FAILED(pInstance->Initialize(_hWnd, _isWindowed, _iWinSizeX, _iWinSizeY, _ppDevice, _ppContext)))
	{
		MSG_BOX("Fail Create Graphic");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CGraphic::Free()
{
}