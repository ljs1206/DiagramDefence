#pragma once
#include "Component.h"

class EnemyGun;
class Player;
class EnemyAttack : public Component
{
public:
	EnemyAttack();
	~EnemyAttack();
public:
	// Component을(를) 통해 상속됨
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void Fire();
	void Init();
public:
	const ENEMY_ATTACK_TYPE const GetEnemyAttackType()
		{ return m_currentAttackType; }
	void SetEnemyAttackType(ENEMY_ATTACK_TYPE type)
	{
		m_currentAttackType = type;
	}
	const EnemyGun* const GetGun()
	{
		return m_myGun;
	}
	void SetGun(EnemyGun* gun)
	{
		m_myGun = gun;
	}
private:
	ENEMY_ATTACK_TYPE m_currentAttackType;
	EnemyGun* m_myGun;
	Object* pPlayer;
};

