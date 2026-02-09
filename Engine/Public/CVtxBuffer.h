#pragma once
#include "CBase.h"

BEGIN(Engine)

class MY_DLL CVtxBuffer : public CBase
{
private:
	CVtxBuffer(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
	~CVtxBuffer() = default;

public:
	HRESULT Initialize();
	void	Update(float _fTimeDelta);
	HRESULT Render();
	HRESULT Bind_Resources();

protected:
	HRESULT Init_VertexBuffer();
	HRESULT Init_IndexBuffer();

protected:
	D3D11_BUFFER_DESC		m_tBufferDesc = { };
	D3D11_SUBRESOURCE_DATA	m_tInitialData = { };

	ID3D11Buffer*		 m_pVertexBuffer = { nullptr };
	ID3D11Buffer*		 m_pIndexBuffer = { nullptr };

	ID3D11Device*		 m_pDevice	= { nullptr };
	ID3D11DeviceContext* m_pContext = { nullptr };

public:
	static CVtxBuffer* Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
	void Free() override;
};

END