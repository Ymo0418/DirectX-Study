#include "CTransform.h"
#include "CShader.h"

CTransform::CTransform(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
	: m_pDevice{ _pDevice }, m_pContext{ _pContext }
{

}

HRESULT CTransform::Initialize()
{
	XMStoreFloat4x4(&m_matWorld, XMMatrixIdentity());

	return S_OK;
}

void CTransform::Set_Scale(XMVECTOR _vScale)
{
	XMVECTOR vRight = XMLoadFloat4x4(&m_matWorld).r[0];
	vRight = XMVector3Normalize(vRight) * XMVectorGetX(_vScale);

	XMVECTOR vUp	= XMLoadFloat4x4(&m_matWorld).r[1];
	vUp = XMVector3Normalize(vUp) * XMVectorGetY(_vScale);

	XMVECTOR vLook	= XMLoadFloat4x4(&m_matWorld).r[2];
	vLook = XMVector3Normalize(vLook) * XMVectorGetZ(_vScale);

	XMStoreFloat4((XMFLOAT4*)(&m_matWorld.m[0][0]), vRight);
	XMStoreFloat4((XMFLOAT4*)(&m_matWorld.m[1][0]), vUp);
	XMStoreFloat4((XMFLOAT4*)(&m_matWorld.m[2][0]), vLook);
}

void CTransform::Set_Rot(XMVECTOR _vRot)
{
	XMVECTOR vRight = XMVector3Normalize(XMLoadFloat4x4(&m_matWorld).r[0]);
	XMVECTOR vUp = XMVector3Normalize(XMLoadFloat4x4(&m_matWorld).r[1]);
	XMVECTOR vLook = XMVector3Normalize(XMLoadFloat4x4(&m_matWorld).r[2]);
	
	//Yaw Ã´Ãß±âÁØ
	//Pit ÆÈ
	//Rol ¾Õ
	XMVECTOR vQuat = XMQuaternionRotationRollPitchYaw(XMVectorGetX(_vRot), 
						XMVectorGetY(_vRot), 
						XMVectorGetZ(_vRot));
	XMMATRIX matRot = XMMatrixRotationQuaternion(vQuat);

	XMStoreFloat4((XMFLOAT4*)(&m_matWorld.m[0][0]), XMVector3TransformNormal(vRight, matRot));
	XMStoreFloat4((XMFLOAT4*)(&m_matWorld.m[1][0]), XMVector3TransformNormal(vUp, matRot));
	XMStoreFloat4((XMFLOAT4*)(&m_matWorld.m[2][0]), XMVector3TransformNormal(vLook, matRot));
}

void CTransform::Set_Pos(XMVECTOR _vPos)
{
	XMStoreFloat4((XMFLOAT4*)(&m_matWorld.m[3][0]), _vPos);
}

XMVECTOR CTransform::Get_Pos()
{
	return XMLoadFloat4((XMFLOAT4*)(&m_matWorld.m[3][0]));
}

void CTransform::Add_Pos(XMVECTOR _vMovement)
{
	XMVECTOR vCurPos = XMLoadFloat4x4(&m_matWorld).r[3];

	Set_Pos(vCurPos + _vMovement);
}

HRESULT CTransform::Bind_Matrix(CShader* _pShader, const char* _pName)
{
	return _pShader->Bind_Matrix(_pName, &m_matWorld);
}

XMMATRIX CTransform::Get_WorldMatrix()
{
	return XMLoadFloat4x4(&m_matWorld);

}

CTransform* CTransform::Create(ID3D11Device* _pDevice,
	ID3D11DeviceContext* _pContext)
{
	CTransform* pInstance = new CTransform(_pDevice, _pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail Create CTransform");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTransform::Free()
{
	__super::Free();

	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
}