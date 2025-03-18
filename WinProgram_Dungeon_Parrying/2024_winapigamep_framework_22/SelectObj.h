#pragma once
#include "Object.h"

class Box;
class SelectObj : public Object
{
public:
	SelectObj(Box* owner);
	~SelectObj();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
public:
	const bool const GetIsSelect() { return m_isSelect; }
	void const SetIsSelect(bool value) { m_isSelect = value; }
	void const SetOwner(Box* box) { m_owner = box; }
	const Box* const GetOwner() { return m_owner; }
	void SetSelectType(SELECT_TYPE type) { m_selectType = type; }
	const SELECT_TYPE* const GetSelectType() { return &m_selectType; }
private:
	void Select();
private:
	bool m_isSelect;
	bool m_canSelect;
	Box* m_owner;

	SELECT_TYPE m_selectType;
	HFONT boxFont;
};

