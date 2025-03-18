#pragma once
class TitleScene;
class WaveManager
{
	DECLARE_SINGLE(WaveManager);
public:
	void Init();
	void Update();
public:
	void WaveStart(int count, float spawnTime);
	void WaveEnd();
	void SetCurrentScene(TitleScene* scene);
public:
	bool GetNowWave() { return m_isWaveNow;  }
private:
	int m_currentWaveCount;
	int m_waveSpawnCount;
	int m_waveMaxSpawnCount;

	float m_spawnTime;
	float m_currentSpawnTime;

	bool m_isWaveNow;

	TitleScene* m_titleScene;
};

