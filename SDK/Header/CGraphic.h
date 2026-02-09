#pragma once
#include "CBase.h"

BEGIN(Engine)

class CGraphic : public CBase
{
private:
	CGraphic();
	virtual ~CGraphic() = default;

public:
	HRESULT Initialize(HWND _hWnd, bool _isWindowed, uint _iWinSizeX, uint _iWinSizeY,
		_Inout_ ID3D11Device** _ppDevice, _Inout_ ID3D11DeviceContext** _ppContext);
	HRESULT Present();
	HRESULT Clear_BackBuffer();
	HRESULT Clear_DepthStencil();

private:
	HRESULT Ready_SwapChain(HWND _hWnd, bool _isWindowed, uint _iWinSizeX, uint _iWinSizeY);
	HRESULT Ready_BackBufferRTV();
	HRESULT Ready_DepthStencilView(uint _iWinSizeX, uint _iWinSizeY);

protected:
	ID3D11Device*			m_pDevice			= { nullptr };
	ID3D11DeviceContext*	m_pContext			= { nullptr };

	IDXGISwapChain*			m_pSwapChain		= { nullptr };
	ID3D11RenderTargetView* m_pBackBufferRTV	= { nullptr };
	
	ID3D11Texture2D*		m_pDepthTexture		= { nullptr };
	ID3D11DepthStencilView* m_pDepthStencilView = { nullptr };

public:
	static CGraphic* Create(HWND _hWnd, bool _isWindowed, uint _iWinSizeX, uint _iWinSizeY,
		ID3D11Device** _ppDevice, ID3D11DeviceContext** _ppContext);
	virtual void Free() override;
};

END