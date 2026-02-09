#pragma once
#include "CObject.h"

BEGIN(Engine)

class CObjectManager :public CBase
{
private:
	CObjectManager();
	virtual ~CObjectManager() = default;

public:
	HRESULT Initialize();
	void	Early_Update(float _fTimeDelta);
	void	Update(float _fTimeDelta);
	void	Late_Update(float _fTimeDelta);
	HRESULT Render();

public:
	HRESULT Add_Object(CObject* _pObj);

private:
	list<CObject*>		m_ObjectList;

public:
	static CObjectManager* Create();
	virtual void Free() override;
};

END