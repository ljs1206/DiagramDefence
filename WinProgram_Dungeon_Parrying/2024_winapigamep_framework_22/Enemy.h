#pragma once
#include "Object.h"
class Enemy :
    public Object
{
public:
	Enemy();
	~Enemy();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
public:
	void SetAngleCount(int count) { m_angleCount = count; }
	void SetMaxHp(int maxHp) { m_hp = maxHp; }
private:
	void MoveToTarget(Vec2 targetPos);
	void Fire();
	void SetStatValue();
private:
	int m_hp;
	int m_fireDamage;
	Object* pPlayer;

	bool m_canMove;
	float m_moveSpeed;
	float m_fireCount;
	float m_bulletSpeed;

	float m_fireCoolTime;
	float m_currentCoolTime;

	int m_angleCount;
};

