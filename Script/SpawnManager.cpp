#include "pch.h"
#include "SpawnManager.h"
#include "TimeManager.h"
#include "Object.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Core.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Box.h"

void SpawnManager::Init()
{
	m_isAllDie = false;
	m_spawnTime = 1.f;
	m_currentTime = 0;
	m_objSize = 25.f;
}

void SpawnManager::Update()
{
	if (m_spawnObjectList.size() <= 0) {
		m_isAllDie = true;
	}
	else{
		m_isAllDie = false;
	}
}

void SpawnManager::SpawnObject(int angleCount)
{
	Enemy* enemy = new Enemy;
	enemy->SetAngleCount(angleCount);
	enemy->SetMaxHp(angleCount - 2);
	enemy->SetPos(GetRandomPos(m_objSize));
	enemy->SetSize(Vec2{ 25.f, 25.f });
	m_spawnObjectList.push_back(enemy);
	GET_SINGLE(SceneManager)->GetCurrentScene()
		->AddObject(enemy, LAYER::ENEMY);
}

void SpawnManager::SetCurrentScene(TitleScene* scene)
{
	m_titleScene = scene;
}

void SpawnManager::SpawnWaveBox()
{
	Box* box = new Box;
	box->SetName(L"Box");
	box->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	box->SetSize({ 50.f, 50.f });
	m_titleScene->AddObject(box, LAYER::BOX);
	m_titleScene->SetIsSpawnBox(true);
}

Vec2 SpawnManager::GetRandomPos(float size)
{
	float x, y;
	int randNum = rand() % 4 + 1;
	
	switch (randNum) {
	case 1:
		x = 0 - size / 2;
		y = rand() % SCREEN_HEIGHT;
		break;
	case 2:
		x = SCREEN_WIDTH + size / 2;
		y = rand() % SCREEN_HEIGHT;
		break;
	case 3:
		y = SCREEN_HEIGHT + size / 2;
		x = rand() % SCREEN_WIDTH;
		break;
	case 4:
		y = SCREEN_HEIGHT + size / 2;
		x = rand() % SCREEN_WIDTH;
		break;
	}

	return Vec2{ x, y };
}
