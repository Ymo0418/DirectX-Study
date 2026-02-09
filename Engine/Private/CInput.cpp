#include "CInput.h"

CInput::CInput()
{

}

HRESULT CInput::Initialize(HINSTANCE _hInst, HWND _hWnd)
{
	m_hWnd = _hWnd;

	if(FAILED(DirectInput8Create(_hInst,
								 DIRECTINPUT_VERSION,
								 IID_IDirectInput8,
								 (void**)&m_pInput, nullptr)))
		return E_FAIL;

	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, 
									  &m_pKeyboard, 
									  nullptr)))
		return E_FAIL;

	m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	m_pKeyboard->SetCooperativeLevel(_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	m_pKeyboard->Acquire();


	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse,
		&m_pMouse,
		nullptr)))
		return E_FAIL;
	m_pMouse->SetDataFormat(&c_dfDIMouse);
	m_pMouse->SetCooperativeLevel(_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	m_pMouse->Acquire();

	return S_OK;
}

void CInput::Update()
{
	m_pKeyboard->GetDeviceState(256, m_Keys);
}

bool CInput::GetKey(unsigned char _keyID)
{
	return (m_Keys[_keyID] & 0x80);
}

CInput* CInput::Create(HINSTANCE _hInst, HWND _hWnd)
{
	CInput* pInstance = new CInput();

	if (FAILED(pInstance->Initialize(_hInst, _hWnd)))
	{
		MSG_BOX("Fail Create Input");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CInput::Free()
{
	Safe_Release(m_pKeyboard);
	Safe_Release(m_pMouse);
	Safe_Release(m_pInput);
}