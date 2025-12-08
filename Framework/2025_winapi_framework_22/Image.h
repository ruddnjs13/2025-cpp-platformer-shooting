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
        bool reverse  = false,                         // 추가
        COLORREF _colorKey = RGB(255, 0, 255)
    )
    {
        int drawWidth = int(_size.x * ratio);
        int srcWidth = int(_texture->GetWidth() * ratio);

        int dstX = int(_pos.x - _size.x / 2);
        int srcX = 0;

        // reverse일 경우 우측에서부터 잘리도록 계산
        if (reverse)
        {
            // 소스의 우측 부분만 가져옴
            srcX = _texture->GetWidth() - srcWidth;

            // 목적지에서도 오른쪽 정렬
            dstX = int(_pos.x + _size.x / 2) - drawWidth;
        }

        TransparentBlt(
            _hdc,
            dstX,
            int(_pos.y - _size.y / 2),
            drawWidth,
            int(_size.y),
            _texture->GetTextureDC(),
            srcX,
            0,
            srcWidth,
            _texture->GetHeight(),
            _colorKey
        );
    }


protected:
	Texture* m_texture = nullptr;

};
