#include "pch.h"
#include "EnemyAttack.h"
#include "EnemyProjectile.h"
#include "EnemyGun.h"
#include "Player.h"
#include "SceneManager.h"
#include "Scene.h"

EnemyAttack::EnemyAttack()
	: m_currentAttackType(ENEMY_ATTACK_TYPE::TRIANGLE)
	, m_myGun(nullptr)
{

}

EnemyAttack::~EnemyAttack()
{
}

void EnemyAttack::LateUpdate()
{
	m_myGun->SetPos(GetOwner()->GetPos());
}

void EnemyAttack::Render(HDC _hdc)
{
}

void EnemyAttack::Fire()
{
	switch (m_currentAttackType) {
	case ENEMY_ATTACK_TYPE::TRIANGLE:
		m_myGun->Fire(80.f);
		m_myGun->SetFireCount(1);
		break;
	case ENEMY_ATTACK_TYPE::SQUARE:
		m_myGun->Fire(55.f);
		m_myGun->SetFireCount(2);
		break;
	case ENEMY_ATTACK_TYPE::PENTAGON:
		m_myGun->Fire(70.f);
		m_myGun->SetFireCount(2);
		break;
	case ENEMY_ATTACK_TYPE::HEXAGON:
		m_myGun->Fire(45.f);
		m_myGun->SetFireCount(3);
		break;
	}
}

void EnemyAttack::Init()
{
	Vec2 vPos = GetOwner()->GetPos();

	m_myGun = new EnemyGun();
	m_myGun->SetPos(vPos);
	m_myGun->SetSize({ 0.f, 0.f });
	pPlayer = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObject(LAYER::PLAYER);
}
