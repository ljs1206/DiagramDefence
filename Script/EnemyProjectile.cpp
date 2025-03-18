#include "pch.h"
#include "EnemyProjectile.h"
#include "EventManager.h"
#include "Collider.h"
#include "TimeManager.h"

EnemyProjectile::EnemyProjectile()
{
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 20.f,20.f });
}

EnemyProjectile::~EnemyProjectile()
{
}

void EnemyProjectile::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void EnemyProjectile::StayCollision(Collider* _other)
{
}

void EnemyProjectile::ExitCollision(Collider* _other)
{
}
