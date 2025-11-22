#include "pch.h"
#include "TestWeapon.h"
#include "ResourceManager.h"

TestWeapon::TestWeapon()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Jiwoo");
	
}

TestWeapon::~TestWeapon()
{
}

void TestWeapon::Update()
{
}

void TestWeapon::Rotate()
{
}

void TestWeapon::Render(HDC _hdc)
{
}

void TestWeapon::Shoot()
{
}
