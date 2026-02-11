#pragma once
#include "LINE.h"
#include "CBase.h"

BEGIN(Engine)

class MY_DLL CNavigation : public CBase
{
protected:
	CNavigation(ID3D11Device* _pDevice,	ID3D11DeviceContext* _pContext);
	~CNavigation() = default;

public:
	HRESULT Initialize();
	float	Calc_Height(XMVECTOR vPrePos, XMVECTOR& vMovement);

#ifdef _DEBUG
	HRESULT Render();
#endif // _DEBUG

private:
	void Set_Neighbor();

private:
	int				m_iCurIdx = { 0 };
	vector<LINE*>	m_Lines;

	ID3D11Device*						m_pDevice	= { nullptr };
	ID3D11DeviceContext*				m_pContext	= { nullptr };
#ifdef _DEBUG
	PrimitiveBatch<VertexPositionColor>* m_pBatch		= { nullptr };
	BasicEffect*						 m_pEffect		= { nullptr };
	ID3D11InputLayout*					 m_pInputLayout = { nullptr };
#endif // _DEBUG

public:
	static CNavigation* Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
	virtual void Free();
};

END