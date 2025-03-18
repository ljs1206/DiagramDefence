#include "pch.h"
#include "Box.h"
#include "Collider.h"
#include "InputManager.h"
#include "SelectObj.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EventManager.h"
#include "GDISelector.h"
#include "TitleScene.h"

Box::Box()
	: m_open(false)
	, m_canOpen(false)
{
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 50.f, 50.f });
}

Box::~Box()
{
}

void Box::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::F) && m_canOpen && !m_open) {
		OpenBox();
	}
}

void Box::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();

	GDISelector* selectPen = nullptr;
	GDISelector* selectBrush = nullptr;
	selectPen = new GDISelector(_hdc, PEN_TYPE::YELLOW);
	selectBrush = new GDISelector(_hdc, BRUSH_TYPE::YELLOW);

	RECT_RENDER(_hdc, vPos.x, vPos.y
		, vSize.x, vSize.y);

	selectPen->~GDISelector();
	selectBrush->~GDISelector();
}

void Box::EnterCollision(Collider* _other)
{
}

void Box::StayCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player") {
		m_canOpen = true;
	}
}

void Box::ExitCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player") {
		m_canOpen = false;
	}
}

void Box::DeleteAllObject()
{
	for (SelectObj* obj : selectList) {
		GET_SINGLE(EventManager)->DeleteObject(obj);
	}
	static_cast<TitleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene().get())
		->SetIsSpawnBox(false);
	GET_SINGLE(EventManager)->DeleteObject(this);
}

void Box::OpenBox()
{
	m_open = true;
	for (int i = 0; i < 5; ++i) {
		SpawnSelect(i);
	}
}

void Box::SpawnSelect(int count)
{
	switch (count) {
	case 0:
	{
		SelectObj* mac = new SelectObj(this);
		mac->SetPos({ GetPos().x - 120, GetPos().y - 60 });
		mac->SetSize({ 30.f, 30.f });
		mac->SetSelectType(SELECT_TYPE::MAGAZINE);
		GET_SINGLE(SceneManager)->
			GetCurrentScene()->AddObject(mac, LAYER::SELECTOBJ);
		Spawn(mac);
	}
		break;
	case 1:
	{
		SelectObj* reload = new SelectObj(this);
		reload->SetPos({ GetPos().x - 60, GetPos().y - 60 });
		reload->SetSize({ 30.f, 30.f });
		reload->SetSelectType(SELECT_TYPE::RELOADINGTIME);
		GET_SINGLE(SceneManager)->
			GetCurrentScene()->AddObject(reload, LAYER::SELECTOBJ);
		Spawn(reload);
	}
		break;
	case 2:
	{
		SelectObj* hp = new SelectObj(this);
		hp->SetPos({ GetPos().x , GetPos().y - 60 });
		hp->SetSize({ 30.f, 30.f });
		hp->SetSelectType(SELECT_TYPE::HP);
		GET_SINGLE(SceneManager)->
			GetCurrentScene()->AddObject(hp, LAYER::SELECTOBJ);
		Spawn(hp);
	}
		break;
	case 3:
	{
		SelectObj* speed = new SelectObj(this);
		speed->SetPos({ GetPos().x + 60, GetPos().y - 60 });
		speed->SetSize({ 30.f, 30.f });
		speed->SetSelectType(SELECT_TYPE::SPEED);
		GET_SINGLE(SceneManager)->
			GetCurrentScene()->AddObject(speed, LAYER::SELECTOBJ);
		Spawn(speed);
	}
	break;
	case 4:
	{
		SelectObj* bullet = new SelectObj(this);
		bullet->SetPos({ GetPos().x + 120, GetPos().y - 60 });
		bullet->SetSize({ 30.f, 30.f });
		bullet->SetSelectType(SELECT_TYPE::BULLETCOUNT);
		GET_SINGLE(SceneManager)->
			GetCurrentScene()->AddObject(bullet, LAYER::SELECTOBJ);
		Spawn(bullet);
	}
	break;
	}
}

void Box::Spawn(SelectObj* obj)
{
	selectList.push_back(obj);
}
