#pragma once
#include "Projectile.h"

class EnemyProjectile : public Projectile
{
public:
	EnemyProjectile();
	~EnemyProjectile();
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
};

