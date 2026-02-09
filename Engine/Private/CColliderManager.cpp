#include "CColliderManager.h"

CColliderManager::CColliderManager()
{
}

HRESULT	CColliderManager::Initialize()
{
	return S_OK;
}

void CColliderManager::Update()
{
	Collide_Group();
	Clear_ColliderGroup();
}

HRESULT CColliderManager::Add_Collider(COLLIDE_GROUP _eGroup, CCollider* _pCollider)
{
	m_CollideGroup[_eGroup].push_back(_pCollider);
	Safe_AddRef(_pCollider);

	return S_OK;
}

void CColliderManager::Collide_Group()
{
	// 원하는 그룹간의 충돌처리

	for (auto& EnemeyCollider : m_CollideGroup[CG_ENEMY])
	{
		for (auto& PlayerCollider : m_CollideGroup[CG_PLAYER])
		{
			PlayerCollider->IsCollide(EnemeyCollider);
		}
	}
}

void CColliderManager::Clear_ColliderGroup()
{
	for (auto& Colliders : m_CollideGroup)
	{
		for (auto& Collider : Colliders)
		{
			Safe_Release(Collider);
		}

		Colliders.clear();
	}
}

CColliderManager* CColliderManager::Create()
{
	CColliderManager* pInstance = new CColliderManager();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail Create CColliderManager");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CColliderManager::Free()
{
	Clear_ColliderGroup();
}