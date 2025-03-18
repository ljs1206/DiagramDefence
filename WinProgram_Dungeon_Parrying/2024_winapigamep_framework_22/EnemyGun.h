#pragma once
#include "Weapon.h"

class EnemyGun : public Weapon
{
public:
	EnemyGun();
	~EnemyGun();
public:
	virtual void Fire(int projSpeed);
	virtual void Update();
public:
	void SetFireCount(int rate) { m_fireCount = rate; }
private:
	bool m_fireNow;
	Object* pPlayer;
	float m_fireRate;
	int m_fireCount;

	void Render(HDC _hdc) override;
	void SetFireDir(Vec2 _dir) override;
};
//
//class EnemyGun : public Weapon
//{
//public:
//	EnemyGun();
//	~EnemyGun();
//public:
//	virtual void Fire();
//private:
//	Object* pPlayer;
//};
//
