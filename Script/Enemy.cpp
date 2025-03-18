#include "pch.h"
#include "Enemy.h"
#include "Collider.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TimeManager.h"
#include "EnemyProjectile.h"
#include "EnemyAttack.h"
#include "SpawnManager.h"

Enemy::Enemy()
	: m_hp(5)
	, m_canMove(true)
	, m_fireCoolTime(2.f)
	, m_currentCoolTime(0)
	, m_moveSpeed(70.f)
	, m_fireDamage(1)
	, m_fireCount(1)
	, m_bulletSpeed(800.f)
{
	this->AddComponent<Collider>();
	this->GetComponent<Collider>()->SetOwner(this);
	this->AddComponent<EnemyAttack>();
	this->GetComponent<EnemyAttack>()->SetOwner(this);
	this->GetComponent<EnemyAttack>()->Init();
	pPlayer = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObject(LAYER::PLAYER);
}
	
Enemy::~Enemy()
{
	GET_SINGLE(SpawnManager)->DeleteObject(this);
}

void Enemy::Update()
{
	Vec2 playerPos = pPlayer->GetPos();
	Vec2 nowPos = GetPos();
	Vec2 dir = playerPos - nowPos;

	if (m_currentCoolTime < m_fireCoolTime) {
		m_currentCoolTime += fDT;
	}

	if (dir.Length() < 200) {
		m_canMove = false;
		if (m_currentCoolTime >= m_fireCoolTime) {
			this->GetComponent<EnemyAttack>()->Fire();
			m_currentCoolTime = 0;
		}
	}
	else {
		m_canMove = true;
	}

	if(m_canMove)
		MoveToTarget(pPlayer->GetPos());

	SetStatValue();
}

void Enemy::Render(HDC _hdc)
{	
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	Vec2 point1, point2, point3, point4, point5, point6;
	POINT points[6];
	float x = vPos.x - vSize.x / 2, y = vPos.y - vSize.y / 2;
	float Radius = 25.f;
	float angle = 360.0f / m_angleCount;
	switch (m_angleCount)
	{
	case 3:
	{
		point1 = Vec2{ vPos.x, vPos.y - vSize.y / 2 };
		point2 = Vec2{ vPos.x + vSize.x / 2, vPos.y + vSize.y / 2 };
		point3 = Vec2{ vPos.x - vSize.x / 2, vPos.y + vSize.y / 2 };
		points[0] = (POINT{ (long)point1.x, (long)point1.y });
		points[1] = (POINT{ (long)point2.x, (long)point2.y });
		points[2] = (POINT{ (long)point3.x, (long)point3.y });
		::Polygon(_hdc, points, m_angleCount);
	}
		break;
	case 4:
	{
		RECT_RENDER(_hdc, vPos.x, vPos.y
			, vSize.x, vSize.y);
	}
		break;
	case 5:
	{
		MoveToEx(_hdc, x, y, NULL);
		for (int i = 0; i < m_angleCount; i++) {
			float nextAngle = (PI * (angle * i)) / 180.0f;
			x = Radius * cosf(nextAngle) + x;
			y = Radius * sinf(nextAngle) + y;
			LineTo(_hdc, x, y);
		}
	}
		break;
	case 6:
		MoveToEx(_hdc, x, y, NULL);
		for (int i = 0; i < m_angleCount; i++) {
			float nextAngle = (PI * (angle * i)) / 180.0f;
			x = Radius * cosf(nextAngle) + x;
			y = Radius * sinf(nextAngle) + y;
			LineTo(_hdc, x, y);
		}
		break;
	default:
		point1 = Vec2{ vPos.x, vPos.y - vSize.y / 2 };
		point2 = Vec2{ vPos.x + vSize.x / 2, vPos.y + vSize.y / 2 };
		point3 = Vec2{ vPos.x - vSize.x / 2, vPos.y + vSize.y / 2 };
		points[0] = (POINT{ (long)point1.x, (long)point1.y });
		points[1] = (POINT{ (long)point2.x, (long)point2.y });
		points[2] = (POINT{ (long)point3.x, (long)point3.y });
		::Polygon(_hdc, points, 3);
		break;
	}
}

void Enemy::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	wstring str = pOtherObj->GetName();
	if (pOtherObj->GetName() == L"PlayerBullet")
	{
		GET_SINGLE(EventManager)->DeleteObject(pOtherObj);
		m_hp -= 1;
		m_angleCount -= 1;
		if(m_hp <= 0)
			GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Enemy::StayCollision(Collider* _other)
{
	//std::cout << "Stay" << std::endl;
}

void Enemy::ExitCollision(Collider* _other)
{
	//std::cout << "Exit" << std::endl;
}

void Enemy::MoveToTarget(Vec2 targetPos)
{
	Vec2 myVec = GetPos();
	Vec2 targetVec = targetPos - myVec;
	targetVec.Normalize();

	myVec.x += (targetVec.x * m_moveSpeed) * fDT;
	myVec.y += (targetVec.y * m_moveSpeed) * fDT;

	SetPos(myVec);
}

void Enemy::Fire()
{
	//this->GetComponent<EnemyAttack>()->Fire();
}

void Enemy::SetStatValue()
{
	switch(m_angleCount)
	{
	case 3:
	{
		m_moveSpeed = 100.f;
		this->GetComponent<EnemyAttack>()
			->SetEnemyAttackType(ENEMY_ATTACK_TYPE::TRIANGLE);
	}
	break;
	case 4:
	{
		m_moveSpeed = 70.f;
		this->GetComponent<EnemyAttack>()
			->SetEnemyAttackType(ENEMY_ATTACK_TYPE::SQUARE);
	}
	break;
	case 5:
	{
		m_moveSpeed = 50.f;
		this->GetComponent<EnemyAttack>()
			->SetEnemyAttackType(ENEMY_ATTACK_TYPE::PENTAGON);
	}
	break;
	case 6:
	{
		m_moveSpeed = 50.f;
		this->GetComponent<EnemyAttack>()
			->SetEnemyAttackType(ENEMY_ATTACK_TYPE::HEXAGON);
	}
		break;
	default:
		this->GetComponent<EnemyAttack>()
			->SetEnemyAttackType(ENEMY_ATTACK_TYPE::TRIANGLE);
		break;
	}
}
