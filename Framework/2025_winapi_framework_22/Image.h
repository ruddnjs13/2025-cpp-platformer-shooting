#pragma once
#include "UIElement.h"
#include "Texture.h"
class Image :
	public UIElement
{
public:
	void Init(Texture* texture);
	void Update() override;
	void Render(HDC _hdc) override;

	inline void DrawTexture(
		HDC _hdc,
		const Vec2& _pos,
		const Vec2& _size,
		Texture* _texture,
		COLORREF _colorKey = RGB(255, 0,255)
	)
	{
		TransparentBlt(
			_hdc,
			int(_pos.x - _size.x / 2),
			int(_pos.y - _size.y / 2),
			int(_size.x),
			int(_size.y),
			_texture->GetTextureDC(),
			0,
			0,
			_texture->GetWidth(),
			_texture->GetHeight(),
			_colorKey
		);
	}

	inline void DrawTextureClipped(
		HDC _hdc,
		const Vec2& _pos,
		const Vec2& _size,
		Texture* _texture,
		float ratio,                 
		COLORREF _colorKey = RGB(255, 0, 255)
	)
	{
		int drawWidth = int(_size.x * ratio);                      
		int srcWidth = int(_texture->GetWidth() * ratio);        

		TransparentBlt(
			_hdc,
			int(_pos.x - _size.x / 2),
			int(_pos.y - _size.y / 2),
			drawWidth,
			int(_size.y),
			_texture->GetTextureDC(),
			0,
			0,
			srcWidth,
			_texture->GetHeight(),
			_colorKey
		);
	}

protected:
	Texture* m_texture = nullptr;

};
