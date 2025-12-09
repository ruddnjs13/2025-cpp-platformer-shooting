
#pragma once
class  UIElement
{
public:
	UIElement();
	virtual ~UIElement();
public:
	virtual void Update() abstract;
	virtual void Render(HDC _hdc) abstract;
public:
	void SetPos(Vec2 _pos) { m_pos = _pos; }
	void SetSize(Vec2 _size) { m_size = _size; }
	const Vec2& GetPos() const { return m_pos; }
	const Vec2& GetSize() const { return m_size; }
	virtual void ClearAllEvents();

public:
	Vec2 m_pos;
	Vec2 m_size;

};

