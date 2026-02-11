#pragma once
#include "CBase.h"

BEGIN(Engine)

class MY_DLL CTransform final : public CBase
{
private:
	CTransform(ID3D11Device* _pDevice,
				ID3D11DeviceContext* _pContext);
	~CTransform() = default;
	
public:
	HRESULT Initialize();
	void Set_Scale(XMVECTOR _vScale);
	void Set_Rot(XMVECTOR _vRot);
	void Set_Pos(XMVECTOR _vPos);
	XMVECTOR Get_Pos();
	void Add_Pos(XMVECTOR _vMovement);
	HRESULT Bind_Matrix(class CShader* _pShader, const char* _pName);
	XMMATRIX Get_WorldMatrix();

protected:
	ID3D11Device*				m_pDevice	= { nullptr };
	ID3D11DeviceContext*		m_pContext	= { nullptr };
	XMFLOAT4X4					m_matWorld	= {};

public:
	static CTransform* Create(ID3D11Device* _pDevice,
						   ID3D11DeviceContext* _pContext);
	virtual void Free() override;
};

END