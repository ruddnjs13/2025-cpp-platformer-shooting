#include "pch.h"
#include "UIElement.h"
#include "Canvas.h"

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

void Canvas::Update()
{
	for (auto element : _vecUIElement)
		element->Update();
}

void Canvas::Render(HDC dc)
{
	for (auto element : _vecUIElement)
		element->Render(dc);
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

void Canvas::Release()
{

}



