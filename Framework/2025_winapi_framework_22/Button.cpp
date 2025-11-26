#include "pch.h"
#include "Button.h"
#include "Texture.h"
#include "InputManager.h"
#include "GDISelector.h"
#include "ResourceManager.h"
#include "Canvas.h"

void Button::Init(Texture* defaultTexture, Texture* hoverTexture)
{
	m_defaultTexture = defaultTexture;
	m_hoverTexture = hoverTexture;

	m_texture = m_defaultTexture;
}

void Button::Update()
{
	Vec2 mousePos = GET_MOUSEPOS;
	

	Vec2 curPos = GetPos();
	Vec2 curSize = GetSize();

	int halfHeight = curSize.y / 2;
	int halfWidth = curSize.x / 2;


	// 이렇게 할거면 모든 UI가 깔끔하게 창 내부에 들어와 있다는 것을 가정함
	if (mousePos.x >= curPos.x - halfWidth
		&& mousePos.x <= curPos.x + halfWidth
		&& mousePos.y <= curPos.y + halfHeight
		&& mousePos.y >= curPos.y - halfHeight)
	{
		OnMouseEnter();
	}
	else
	{
		OnMouseExit();
	}
}

void Button::Render(HDC _hdc)
{
	Image::Render(_hdc);
}

void Button::OnClick()
{
	if (_isClicked) return;

	_isClicked = true;
	OnClickEvt.Invoke();
}

void Button::OnMouseEnter()
{
	if (_isHovered) return;
	_isHovered = true;

	if (m_hoverTexture == NULL) return;
	m_texture = m_hoverTexture;

}

void Button::OnMouseExit()
{
	if (!_isHovered) return;
	_isHovered = false;

	if (m_defaultTexture == NULL) return;
	m_texture = m_defaultTexture;
}
