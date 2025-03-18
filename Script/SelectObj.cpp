#include "pch.h"
#include "SelectObj.h"
#include "Collider.h"
#include "InputManager.h"
#include "EventManager.h"
#include "Box.h"
#include "GDISelector.h"
#include "Object.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Stat.h"
#include "StatSystem.h"
#include "Player.h"

SelectObj::SelectObj(Box* owner)
	: m_isSelect(false)
	, m_canSelect(false)
	, m_owner(nullptr)
	, m_selectType(SELECT_TYPE::NONE)
{
	m_owner = owner;
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 30.f, 30.f});

	boxFont = CreateFont(15, 5, 0, 0, 0, 0, 0, 0, LANG_ENGLISH, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, L"¸¼Àº °íµñ");
}

SelectObj::~SelectObj()
{
}

void SelectObj::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::F) && m_canSelect) {
		Select();
	}
}

void SelectObj::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	GDISelector* selectPen = nullptr;
	GDISelector* selectBrush = nullptr;
	wstring text;

	switch (m_selectType) {
	case SELECT_TYPE::MAGAZINE:
		text = L"Magazine";
		selectPen = new GDISelector(_hdc, PEN_TYPE::HOLLOW);
		selectBrush = new GDISelector(_hdc, BRUSH_TYPE::MAC);
		break;
	case SELECT_TYPE::RELOADINGTIME:
		text = L"ReloadTime";
		selectPen = new GDISelector(_hdc, PEN_TYPE::HOLLOW);
		selectBrush = new GDISelector(_hdc, BRUSH_TYPE::RELOAD);
		break;
	case SELECT_TYPE::HP:
		text = L"HP";
		selectPen = new GDISelector(_hdc, PEN_TYPE::GREEN);
		selectBrush = new GDISelector(_hdc, BRUSH_TYPE::HP);
		break;
	case SELECT_TYPE::SPEED:
		text = L"Speed";
		selectPen = new GDISelector(_hdc, PEN_TYPE::BLUE);
		selectBrush = new GDISelector(_hdc, BRUSH_TYPE::SPEED);
		break;
	case SELECT_TYPE::BULLETCOUNT:
		text = L"BulletCount";
		selectPen = new GDISelector(_hdc, PEN_TYPE::HOLLOW);
		selectBrush = new GDISelector(_hdc, BRUSH_TYPE::BULLETCOUNT);
		break;
	}

	RECT_RENDER(_hdc, vPos.x, vPos.y
		, vSize.x, vSize.y);

	GDISelector font = GDISelector(_hdc, boxFont);

	SetTextAlign(_hdc, TA_CENTER);
	SetBkMode(_hdc, TRANSPARENT);
	::TextOut(_hdc, GetPos().x, (GetPos().y - GetSize().y), text.c_str(), text.length());
	selectPen->~GDISelector();
	selectBrush->~GDISelector();
}

void SelectObj::EnterCollision(Collider* _other)
{
	m_canSelect = true;
}

void SelectObj::StayCollision(Collider* _other)
{
}

void SelectObj::ExitCollision(Collider* _other)
{
	m_canSelect = false;
}

void SelectObj::Select()
{
	Object* pObj = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObject(LAYER::PLAYER);
	Player* pPlayer = static_cast<Player*>(pObj);

	switch (m_selectType) {
	case SELECT_TYPE::MAGAZINE:
		pPlayer->GetStatSystem()->GetStat(STAT_TYPE::MAGAZINE)->Value++;
		break;
	case SELECT_TYPE::RELOADINGTIME:
		pPlayer->GetStatSystem()->GetStat(STAT_TYPE::RELOADINGTIME)->Value -= 0.07f;
		break;
	case SELECT_TYPE::HP:
		pPlayer->GetStatSystem()->GetStat(STAT_TYPE::HP)->Value++;
		break;
	case SELECT_TYPE::SPEED:
		pPlayer->GetStatSystem()->GetStat(STAT_TYPE::SPEED)->Value += 1.f;
		break;
	case SELECT_TYPE::BULLETCOUNT:
		pPlayer->GetStatSystem()->GetStat(STAT_TYPE::BULLETCOUNT)->Value++;
		break;
	}

	m_owner->DeleteAllObject();
}
