#include "CObjectManager.h"

CObjectManager::CObjectManager()
{

}

HRESULT CObjectManager::Initialize()
{
	return S_OK;
}

void CObjectManager::Early_Update(float _fTimeDelta)
{
	for (auto obj : m_ObjectList)
	{
		obj->Early_Update(_fTimeDelta);
	}
}

void CObjectManager::Update(float _fTimeDelta)
{
	for (auto obj : m_ObjectList)
	{
		obj->Update(_fTimeDelta);
	}
}

void CObjectManager::Late_Update(float _fTimeDelta)
{
	for (auto obj : m_ObjectList)
	{
		obj->Late_Update(_fTimeDelta);
	}
}

HRESULT CObjectManager::Render()
{
	for (auto obj : m_ObjectList)
	{
		if (FAILED(obj->Render()))
		{
			__debugbreak();
			return E_FAIL;
		}
	}

	return S_OK;
}

HRESULT CObjectManager::Add_Object(CObject* _pObj)
{
	m_ObjectList.push_back(_pObj);

	return S_OK;
}

CObjectManager* CObjectManager::Create()
{
	CObjectManager* pInstance = new CObjectManager();

	if (FAILED(pInstance->Initialize()))
	{
		__debugbreak();
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CObjectManager::Free()
{
	for (auto obj : m_ObjectList)
		Safe_Release(obj);

	m_ObjectList.clear();
}