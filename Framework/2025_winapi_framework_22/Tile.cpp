#include "pch.h"
#include "Tile.h"
#include "Collider.h"
#include "Texture.h"

Tile::Tile()
{
	AddComponent<Collider>();
}

Tile::Tile(Texture* tileTexture)
{
	m_Texture = tileTexture;
    auto* col = AddComponent<Collider>();
    col->SetSize({ 32,32 });
    col->SetName(L"Floor");
}

Tile::~Tile()
{
}

void Tile::Update()
{
}

void Tile::Render(HDC _hdc)
{
    ComponentRender(_hdc);

    Vec2 curPos = GetPos();
    Vec2 curSize = GetSize();

    HDC hMemDC = m_Texture->GetTextureDC();

    TransparentBlt(
        _hdc,                         
        curPos.x - curSize.x / 2,     
        curPos.y - curSize.y / 2,     
        curSize.x,                    
        curSize.y,                    
        hMemDC,                       
        0,                            
        0,                            
        curSize.x/2,
        curSize.y/2,
        RGB(255,0,255)
    );

}
