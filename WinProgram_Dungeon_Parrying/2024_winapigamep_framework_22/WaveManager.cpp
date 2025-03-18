#include "pch.h"
#include "WaveManager.h"
#include "TimeManager.h"
#include "SpawnManager.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Scene.h"
#include "Box.h"

void WaveManager::Init()
{
	m_currentWaveCount = 0;
	m_waveSpawnCount = 0;
}

void WaveManager::Update()
{
	if (!m_isWaveNow)
	{
		return;
	}

	int randNum;
	if (m_waveSpawnCount >= m_waveMaxSpawnCount)
	{
		if (GET_SINGLE(SpawnManager)->GetAllDie()) {
			WaveEnd();
		}
		return;
	}

	if (m_currentSpawnTime < m_spawnTime) {
		m_currentSpawnTime += fDT;
	}
	else if (m_currentSpawnTime >= m_spawnTime) {
		int maxAngleCount =
			static_cast<TitleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene().get())
			->GetTypeOfEnemyMax();
		m_currentSpawnTime = 0;
		randNum = rand() % 6 + 1;
		randNum = std::clamp(randNum, 3, maxAngleCount);
		GET_SINGLE(SpawnManager)->SpawnObject(randNum);
		m_waveSpawnCount++;
	}
}

void WaveManager::WaveStart(int count, float spawnTime)
{
	cout << "WaveStart\n";
	GET_SINGLE(SpawnManager)->SetAllDie(false);
	m_isWaveNow = true;
	m_waveMaxSpawnCount = count;
	m_spawnTime = spawnTime;
}

void WaveManager::WaveEnd()
{
	TitleScene* scene = 
		static_cast<TitleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene().get());
	m_isWaveNow = false;
	GET_SINGLE(SpawnManager)->SpawnWaveBox();
	scene->SetIsSpawnBox(true);
	m_currentWaveCount++;
	m_waveSpawnCount = 0;
	scene->SetTypeOfEnemyMax(m_currentWaveCount + 3);
}

void WaveManager::SetCurrentScene(TitleScene* scene)
{
	m_titleScene = scene;
}
