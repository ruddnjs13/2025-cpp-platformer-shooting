#include "pch.h"
#include "UIElement.h"
#include "Canvas.h"

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
	Release();
}

void Canvas::Update()
{
	for (auto element : _vecUIElement)
		if(element !=nullptr)
			element->Update();
}

void Canvas::Render(HDC dc)
{
	for (auto element : _vecUIElement)
		if (element != nullptr)
			element->Render(dc);
}

void Canvas::Release()
{
	for (auto element : _vecUIElement)
	{
		SAFE_DELETE(element);
	}
	_vecUIElement.clear();
}

void Canvas::AddUIElement(UIElement* uiElement)
{
	_vecUIElement.push_back(uiElement);
}

void Canvas::RemoveOjbect(UIElement* uiElement)
{
	auto iter = std::find(_vecUIElement.begin(), _vecUIElement.end(), uiElement);
	SAFE_DELETE(*iter);
	_vecUIElement.erase(iter);
}
