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
	AddComponent<Rigidbody>();
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
}
