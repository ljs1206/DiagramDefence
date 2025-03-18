#include "pch.h"
#include "Weapon.h"
#include "EnemyGun.h"
#include "EnemyProjectile.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Stat.h"
#include "TimeManager.h"
//
//EnemyGun::EnemyGun()
//{
//	pPlayer = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObject(LAYER::PLAYER);
//}
//
//EnemyGun::~EnemyGun()
//{
//}
//
//void EnemyGun::Fire()
//{
//	if (m_currentMagazine <= 0 || m_isFire == true || m_isReloading == true) return;
//	this->m_isFire = true;
//
//	m_currentQuickCount = m_bulletMultiplier;
//	if (m_currentMagazine >= 0)
//	{
//		m_isQuick = true;
//	}
//
//	EnemyProjectile* pProj = new EnemyProjectile;
//	Vec2 vPos = m_firePos;
//	pProj->SetPos(vPos);
//
//	Vec2 myVec = this->m_firePos;
//	Vec2 playerPos = pPlayer->GetPos();
//	Vec2 targetVec = playerPos - myVec;
//
//	float angle = atan2(targetVec.y, targetVec.x);
//	Vec2 dir;
//	dir.x = cos(angle);
//	dir.y = sin(angle);
//	pProj->SetDir(dir);
//	pProj->SetAngle(angle);
//	pProj->SetName(L"EnemyBullet");
//
//	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
//
//	SetCurrentMagazine(--m_currentMagazine);
//	this->m_isFire = false;
//}

EnemyGun::EnemyGun()
{
	m_fireRate = 0.5f;
	pPlayer = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObject(LAYER::PLAYER);
}

EnemyGun::~EnemyGun()
{
}

void EnemyGun::Fire(int projSpeed)
{
	if (m_isFire == true) return;
	this->m_isFire = true;
	while (m_fireCount > 0) {
		if (m_fireNow) continue;
		EnemyProjectile* pProj = new EnemyProjectile;
		Vec2 vPos = GetPos();
		pProj->SetPos(vPos);
		pProj->SetProjSpeed(projSpeed);

		Vec2 myVec = vPos;
		Vec2 playerPos = pPlayer->GetPos();
		Vec2 targetVec = playerPos - myVec;

		float angle = atan2(targetVec.y, targetVec.x);
		Vec2 dir;
		dir.x = cos(angle);
		dir.y = sin(angle);
		pProj->SetDir(dir);
		pProj->SetAngle(angle);
		pProj->SetName(L"EnemyBullet");

		
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
		
		if (m_fireRate - 1 <= 0) {
			break;
		}
		m_fireNow = true;
	}
	this->m_isFire = false;
}

void EnemyGun::Update()
{
	if (m_fireNow) {
		float currnetTime = 0.f;
		if (currnetTime < m_fireRate)
			currnetTime += fDT;
		else
		{
			m_fireNow = false;
			m_fireRate--;
		}
	}
}

void EnemyGun::Render(HDC _hdc)
{

}

void EnemyGun::SetFireDir(Vec2 _dir)
{

}
