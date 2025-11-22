#include "pch.h"
#include "TestBullet.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Collider.h"
#include "Rigidbody.h"

TestBullet::TestBullet()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Bullet");
}

TestBullet::~TestBullet()
{

}

void TestBullet::Update()
{

}

void TestBullet::BurstBullet()
{

}

void TestBullet::Rotate()
{

}
