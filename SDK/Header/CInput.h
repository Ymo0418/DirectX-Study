#pragma once
#include "CBase.h"

BEGIN(Engine)

class CInput final : public CBase
{
private:
	CInput();
	virtual ~CInput() = default;
	
public:
	HRESULT Initialize(HINSTANCE _hInst, HWND _hWnd);
	void	Update();

	bool	GetKey(unsigned char _keyID);
	
private:
	HWND					m_hWnd		= {};
	LPDIRECTINPUT8			m_pInput	= { nullptr };
	LPDIRECTINPUTDEVICE8	m_pKeyboard = { nullptr };
	LPDIRECTINPUTDEVICE8	m_pMouse	= { nullptr };

	char					m_Keys[256] = {};

public:
	static CInput* Create(HINSTANCE _hInst, HWND _hWnd);
	virtual void Free();

};

END