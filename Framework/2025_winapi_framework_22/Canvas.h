#pragma once

class UIElement;

class Canvas
{
public:
	Canvas();
	virtual ~Canvas();

public:
	virtual void Init() abstract;
	virtual void Update();
	virtual void Render(HDC dc);
	//virtual void Release();

public:
	void AddUIElement(UIElement* uiElement);
	void RemoveOjbect(UIElement* uiElement);

private:
	vector<UIElement*> _vecUIElement;
};

