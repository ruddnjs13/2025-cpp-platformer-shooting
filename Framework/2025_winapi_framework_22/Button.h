#pragma once
#include "Image.h"
#include "MyAction.h"

class Texture;

class Button :
    public Image
{
public:
    void Init(Texture* defaultTexture, Texture* selectTexture);
    void Update() override;
    void Render(HDC _hdc) override;
public:
    void OnClick();
    void ClearAllEvents() override;
public:
    void OnMouseEnter();
    void OnMouseExit();
private:
    bool _isClicked = false;
    bool _isHovered = false;
private:
    Texture* m_defaultTexture = nullptr;
    Texture* m_hoverTexture = nullptr;
public:
    MyAction<void> OnClickEvt;
};

