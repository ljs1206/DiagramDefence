#pragma once
#include "Object.h"

class SelectObj;
class Box : public Object
{
public:
	Box();
	~Box();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
public:
	void DeleteAllObject();
private:
	void OpenBox();
	void SpawnSelect(int count);
	void Spawn(SelectObj* obj);
private:
	bool m_open;
	bool m_canOpen;
	vector<SelectObj*> selectList;
};