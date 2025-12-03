#include "pch.h"
#include "SlotReel.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TestWeapon.h"
#include "RollingItem.h"
#include "TestWeapon2.h"
#include "SceneManager.h"
#include "Collider.h"
#include "WeaponHolderComponent.h"
#include <math.h>
#include <thread>

SlotReel::SlotReel()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Test2");
	srand(static_cast<unsigned int>(time(nullptr)));

	auto* col = AddComponent<Collider>();
	col->SetName(L"Rolling");
	col->SetTrigger(true);
	col->SetSize({ 30.f, 5.f });
	Vec2 pos = GetPos();
	pos.y -= 6;
	col->SetOffSetPos(pos);
	
	m_pWeaponHolder = AddComponent<WeaponHolderComponent>();

	m_pWeaponHolder->ChangeWeapon(new TestWeapon(),
		{ pos },
		{ 20.f,20.f });
}

SlotReel::~SlotReel()
{

}

void SlotReel::Update()
{

}

void SlotReel::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	LONG width = m_pTex->GetWidth();
	LONG height = m_pTex->GetHeight();
	
	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, m_pTex->GetTextureDC()
		, 0, 0, width, height,
		RGB(255, 0, 255));
}

void SlotReel::EnterCollision(Collider* _other)
{
}

void SlotReel::StayCollision(Collider* _other)
{
}

void SlotReel::ExitCollision(Collider* _other)
{
}

void SlotReel::SlotRolling()
{
	rollingVec.clear();

	int randoCnt = rand() % 50 + 26;

	Vec2 offsetPos = GetPos();

	for (int i = 0; i < 3; i++)
	{
		
		int randoCnt = rand() % 3 + 1;
		RollingItem* rollingItem = new RollingItem;

		switch (randoCnt)
		{
		case 1:
			rollingItem->SetSize({ 25,25 });
			rollingItem->SetPos(offsetPos);
			rollingItem->SetTexture(L"Plane");
			break;
		case 2:
			rollingItem->SetSize({ 25,25 });
			rollingItem->SetPos(offsetPos);
			rollingItem->SetTexture(L"Bullet");
			break;
		case 3:
			rollingItem->SetSize({ 25,25 });
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
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			int randomInt = rand() % 50 + 26;
			Vec2 offsetPoss = GetPos();
			offsetPoss.y -= 60;
			float speed = 100;
			int responTime = 250;

	
			for (int i = 0; i < 25; ++i)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(responTime));

				GET_SINGLE(SceneManager)->RequestDestroy(rollingVec[0]);

				rollingVec[0] = rollingVec[1];
				rollingVec[1] = rollingVec[2];

				if (speed <= 15)
				{
					speed = 0;
				}

				for (int i = 0; i < rollingVec.size()-1; i++)
				{
					rollingVec[i]->SetDownSpeed(speed);
				}



				RollingItem* rollingItems = new RollingItem;

				int randomTexture = rand() % 3 + 1;
				switch (randomTexture)
				{
				case 1:
					rollingItems->SetSize({ 25,25 });
					rollingItems->SetPos(offsetPoss);
					rollingItems->SetTexture(L"Bullet");
					rollingItems->SetDownSpeed(speed);
					break;
				case 2:
					rollingItems->SetSize({ 25,25 });
					rollingItems->SetPos(offsetPoss);
					rollingItems->SetTexture(L"Gun1");
					rollingItems->SetDownSpeed(speed);
					break;
				case 3:
					rollingItems->SetSize({ 25,25 });
					rollingItems->SetPos(offsetPoss);
					rollingItems->SetTexture(L"Bullet");
					rollingItems->SetDownSpeed(speed);
					break;
				}
				GET_SINGLE(SceneManager)->GetCurScene()->AddObject(rollingItems, Layer::RollItem);

				rollingVec[2] = rollingItems;

				speed -= 4;
				responTime += 50;

				

				if (i == 24)
				{
				
					switch (randomTexture)
					{
					case 1:
					{
						m_pWeaponHolder->SetOwner(GetOwner());
						Vec2 pos = GetOwner()->GetPos();
						pos.y -= GetOwner()->GetSize().y / 2.f;
						pos.x += 10.f;
						Vec2 angle = Vec2(0.f, 0.f);
				
						m_pWeaponHolder->ChangeWeapon(new TestWeapon(),
							{ pos },
							{ 20.f,20.f });
				
				
						GET_SINGLE(SceneManager)->GetCurScene()->AddObject(m_pWeaponHolder->GetCurrentWeapon(), Layer::Weapon);
					}
						break;
					case 2:
					{
						m_pWeaponHolder->SetOwner(GetOwner());
						Vec2 pos = GetOwner()->GetPos();
						pos.y -= GetOwner()->GetSize().y / 2.f;
						pos.x += 10.f;
						Vec2 angle = Vec2(0.f, 0.f);
				
						m_pWeaponHolder->ChangeWeapon(new TestWeapon2(),
							{ pos },
							{ 20.f,20.f });
				
				
						GET_SINGLE(SceneManager)->GetCurScene()->AddObject(m_pWeaponHolder->GetCurrentWeapon(), Layer::Weapon);
					}
						break;
					case 3:
					{
						m_pWeaponHolder->SetOwner(GetOwner());
						Vec2 pos = GetOwner()->GetPos();
						pos.y -= GetOwner()->GetSize().y / 2.f;
						pos.x += 10.f;
						Vec2 angle = Vec2(0.f, 0.f);
				
						m_pWeaponHolder->ChangeWeapon(new TestWeapon(),
							{ pos },
							{ 20.f,20.f });
				
				
						GET_SINGLE(SceneManager)->GetCurScene()->AddObject(m_pWeaponHolder->GetCurrentWeapon(), Layer::Weapon);
					}
						break;
					}
				}
				
			}
		}).detach();
}



