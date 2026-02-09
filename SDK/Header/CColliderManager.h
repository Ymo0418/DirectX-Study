#pragma once
#include "CBounding_AABB.h"
#include "CBounding_OBB.h"
#include "CBounding_Sphere.h"

BEGIN(Engine)

class CColliderManager final : public CBase
{
public:
	enum COLLIDE_GROUP { CG_PLAYER, CG_ENEMY, CG_END };

protected:
	CColliderManager();
	virtual ~CColliderManager() = default;

public:
	HRESULT		Initialize();
	void		Update();
	HRESULT		Add_Collider(COLLIDE_GROUP _eGroup, CCollider* _pCollider);

private:
	void		Collide_Group();
	void		Clear_ColliderGroup();

private:
	vector<CCollider*> m_CollideGroup[CG_END];

public:
	static CColliderManager* Create();
	virtual void Free();
};

END