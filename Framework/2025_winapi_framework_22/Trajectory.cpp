#include "pch.h"
#include "Trajectory.h"
#include "Texture.h"
#include "Rigidbody.h"
#include "ResourceManager.h";
#include "TextureObject.h"
#include "SceneManager.h"
#include <thread>

Trajectory::Trajectory()
{
	//m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"AimLine");
	//AddComponent<Rigidbody>();
}

Trajectory::~Trajectory()
{
}

void Trajectory::Update()
{
	Translate({ m_dir.x * 500.f * fDT, m_dir.y * 500.f * fDT });
}

void Trajectory::Render(HDC _hdc)
{
	//Vec2 pos = GetPos();
	//Vec2 size = GetSize();
	//LONG width = m_pTex->GetWidth();
	//LONG height = m_pTex->GetHeight();
	//
	//::TransparentBlt(_hdc
	//	, (int)(pos.x - size.x / 2)
	//	, (int)(pos.y - size.y / 2)
	//	, size.x
	//	, size.y
	//	, m_pTex->GetTextureDC()
	//	, 0, 0, width, height,
	//	RGB(255, 0, 255));
}
