#pragma once
class Object;
class Enemy;
class TitleScene;
class SpawnManager
{
	DECLARE_SINGLE(SpawnManager);
public:
	void Init();
	void Update();
	void SpawnObject(int angleCount);
	void SetCurrentScene(TitleScene* scene);
public:
	const bool GetAllDie() {
		return m_isAllDie;
	}
	 void SetAllDie(bool value) {
		m_isAllDie = value;
	}
	vector<Enemy*> GetSpawnList()
	{
		return m_spawnObjectList;
	}

	void SetAllDieEvent(void(*func)()) {
		fcnPtr = func;
	}
	void SetSpawnTime(float value) {
		m_spawnTime = value;
	}
	void SetSpawnType(int angleCount) { m_currentSpawnInt = angleCount; }
public:
	void DeleteObject(Enemy* enemy) {
		if (enemy == nullptr) return;
		vector<Enemy*>::iterator iter =
			std::find(m_spawnObjectList.begin(),
				m_spawnObjectList.end(), enemy);
		m_spawnObjectList.erase(iter);
	}
	void SpawnWaveBox();
private:
	Vec2 GetRandomPos(float size);
private:
	vector<Enemy*> m_spawnObjectList;
	int m_currentSpawnInt;
	float m_currentTime;
	float m_spawnTime;
	int m_objSize;

	TitleScene* m_titleScene;
	bool m_isAllDie;

	void (*fcnPtr)();
};

