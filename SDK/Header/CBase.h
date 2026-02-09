#pragma once
#include "Engine_Define.h"

BEGIN(Engine)

class MY_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;
public:
	uint AddRef();
	uint Release();

protected:
	uint m_iRefCnt = { 0 };

public:
	virtual void Free();
};

END