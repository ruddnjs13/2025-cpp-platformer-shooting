#pragma once
#include "Object.h"

class Texture;

class Tile :
    public Object
{
public:
    Tile();
    Tile(Texture* tileTexture);
    ~Tile();

    // Object을(를) 통해 상속됨
    void Update() override;

    void Render(HDC _hdc) override;

    void SetCollSize(Vec2 size);

private:
    Texture* m_Texture;
};

