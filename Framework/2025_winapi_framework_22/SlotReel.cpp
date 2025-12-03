#include "pch.h"
#include "SlotReel.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TestWeapon.h"
#include "RollingItem.h"
#include "SceneManager.h"
#include <math.h>
#include <thread>

SlotReel::SlotReel()
{
	//m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"AimLine");
	srand(static_cast<unsigned int>(time(nullptr)));
}

SlotReel::~SlotReel()
{

}

void SlotReel::Update()
{

}

void SlotReel::Render(HDC _hdc)
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

Weapon* SlotReel::SlotRolling()
{
	int randoCnt = rand() % 50 + 26;

	Vec2 offsetPos = GetPos();

	for (int i = 0; i < 3; i++)
	{
		
		int randoCnt = rand() % 3 + 1;
		RollingItem* rollingItem = new RollingItem;

		switch (randoCnt)
		{
		case 1:
			rollingItem->SetSize({ 30,30 });
			rollingItem->SetPos(offsetPos);
			rollingItem->SetTexture(L"Plane");
			break;
		case 2:
			rollingItem->SetSize({ 30,30 });
			rollingItem->SetPos(offsetPos);
			rollingItem->SetTexture(L"Bullet");
			break;
		case 3:
			rollingItem->SetSize({ 30,30 });
			rollingItem->SetPos(offsetPos);
			rollingItem->SetTexture(L"Jiwoo");
			break;
		}
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(rollingItem, Layer::DEFAULT);

		offsetPos.y -= 30;

		rollingVec.push_back(rollingItem);
	}

	std::thread([this]()
		{
			int randomInt = rand() % 50 + 26;
			Vec2 offsetPoss = GetPos();
			offsetPoss.y -= 60;
			float speed = 100;
			int responTime = 250;

			for (int i = 0; i < 20; ++i)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(responTime));

				GET_SINGLE(SceneManager)->RequestDestroy(rollingVec[0]);

				rollingVec[0] = rollingVec[1];
				rollingVec[1] = rollingVec[2];


				RollingItem* rollingItems = new RollingItem;

				int randomTexture = rand() % 3 + 1;
				switch (randomTexture)
				{
				case 1:
					rollingItems->SetSize({ 30,30 });
					rollingItems->SetPos(offsetPoss);
					rollingItems->SetTexture(L"Plane");
					rollingItems->SetDownSpeed(speed);
					break;
				case 2:
					rollingItems->SetSize({ 30,30 });
					rollingItems->SetPos(offsetPoss);
					rollingItems->SetTexture(L"Bullet");
					rollingItems->SetDownSpeed(speed);
					break;
				case 3:
					rollingItems->SetSize({ 30,30 });
					rollingItems->SetPos(offsetPoss);
					rollingItems->SetTexture(L"Jiwoo");
					rollingItems->SetDownSpeed(speed);
					break;
				}
				GET_SINGLE(SceneManager)->GetCurScene()->AddObject(rollingItems, Layer::DEFAULT);

				rollingVec[2] = rollingItems;

				speed -= 5;
				responTime += 20;

				if (i == randomInt - 1)
				{
					selectWeapon = new TestWeapon;
				}
			}
		}).detach();

	return selectWeapon;
}



