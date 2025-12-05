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


	auto* col = AddComponent<Collider>();
	col->SetName(L"Rolling");
	col->SetTrigger(true);
	col->SetSize({ 30.f, 5.f });
	Vec2 pos = GetPos();
	pos.y -= 6;
	col->SetOffSetPos(pos);
	
	m_pWeaponHolder = AddComponent<WeaponHolderComponent>();

	//m_pWeaponHolder->ChangeWeapon(new TestWeapon(),
	//	{ pos },
	//	{ 20.f,20.f });
}

SlotReel::~SlotReel()
{
	m_pWeaponHolder->DestroyWeapon();
}

void SlotReel::Update()
{

}

void SlotReel::Render(HDC _hdc)
{
	if (m_pTex != NULL)
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

}

void SlotReel::SetRollingTexture(RollingItem* rollItem,wstring textureName, Vec2 offsetPos, float speed)
{
	rollItem->SetSize({ 25,25 });
	rollItem->SetPos(offsetPos);
	rollItem->SetTexture(textureName);
	rollItem->SetDownSpeed(speed);
}

void SlotReel::SetStartTexture(RollingItem* rollItem, wstring textureName, Vec2 offsetPos)
{
	rollItem->SetSize({ 25,25 });
	rollItem->SetPos(offsetPos);
	rollItem->SetTexture(textureName);
}

void SlotReel::MakeWeapon(Weapon* targetWeapon, int _playerNum)
{
	m_pWeaponHolder->SetOwner(GetOwner());
	Vec2 pos = GetOwner()->GetPos();
	pos.y -= GetOwner()->GetSize().y / 2.f;
	pos.x += 10.f;
	Vec2 angle = Vec2(0.f, 0.f);

	m_pWeaponHolder->ChangeWeapon(targetWeapon,
		{ pos },
		{ 20.f,20.f }
	, _playerNum);


	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(m_pWeaponHolder->GetCurrentWeapon(), Layer::Weapon);
}

void SlotReel::DestroyWeapon()
{
	std::thread([this]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			m_pWeaponHolder->DestroyWeapon();
		}).detach();
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

void SlotReel::SlotRolling(int _playerNum)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	SetPlayerNum(_playerNum);
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Test2");

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
			SetStartTexture(rollingItem, L"Gun1", offsetPos);
			break;
		case 2:
			SetStartTexture(rollingItem, L"Bullet", offsetPos);
			break;
		case 3:
			SetStartTexture(rollingItem, L"Gun1", offsetPos);
			break;
		}
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(rollingItem, Layer::DEFAULT);

		offsetPos.y -= 30;

		rollingVec.push_back(rollingItem);
	}

	std::thread([this]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			int randomInt = rand() % 50 + 26;
			Vec2 offsetPoss = GetPos();
			offsetPoss.y -= 60;
			float speed = 100;
			int responTime = 250;
			int storeValue = 0;
			int playerNum = GetPlayerNum();

			vector<RollingItem*> rollingItem;

			for (int i = 0; i < 25; ++i)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(responTime));

				if (rollingVec.size() >= 3)
				{

					rollingItem.push_back(rollingVec[0]);

					///GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(rollingVec[0]);

					rollingVec[0] = rollingVec[1];
					rollingVec[1] = rollingVec[2];
				}
				else
				{
					if (rollingVec.size() >= 1)
					{
						GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(rollingVec[0]);
					}

					if (rollingVec.size() >= 2)
					{
						rollingVec[0] = rollingVec[1];
					}

					if (rollingVec.size() >= 3)
					{
						rollingVec[1] = rollingVec[2];
					}
				}

				if (speed <= 15)
				{
					speed = 0;
				}

				for (int i = 0; i < rollingVec.size() - 1; i++)
				{
					if (rollingVec[i])
					{
						rollingVec[i]->SetDownSpeed(speed);
					}
				}

				RollingItem* rollingItems = new RollingItem;

				srand(static_cast<unsigned int>(time(nullptr)));

				int randomTexture = rand() % 4 + 1;

				if (i == 22)
				{
					storeValue = randomTexture;
				}

				cout << randomTexture << endl;

				switch (randomTexture)
				{
				case 1:
					SetRollingTexture(rollingItems, L"Bullet", offsetPoss, speed);
					break;
				case 2:
					SetRollingTexture(rollingItems, L"Gun1", offsetPoss, speed);
					break;
				case 3:
					SetRollingTexture(rollingItems, L"Bullet", offsetPoss, speed);
					break;
				case 4:
					SetRollingTexture(rollingItems, L"Gun1", offsetPoss, speed);
					break;

				}
				GET_SINGLE(SceneManager)->GetCurScene()->AddObject(rollingItems, Layer::RollItem);


				if (rollingVec.size() < 3)
				{
					rollingVec.resize(3, nullptr);
				}
				rollingVec[2] = rollingItems;

				speed -= 4.1f;
				responTime += 49;


				if (i == 24)
				{
					switch (storeValue)
					{
					case 1:
						MakeWeapon(new TestWeapon, playerNum);
						break;
					case 2:
						MakeWeapon(new TestWeapon2, playerNum);
						break;
					case 3:
						MakeWeapon(new TestWeapon, playerNum);
						break;
					case 4:
						MakeWeapon(new TestWeapon2, playerNum);
						break;
					}

					for (int i = 0; i < rollingVec.size() - 1; i++)
					{
						if (rollingVec[i])
						{
							GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(rollingVec[i]);
							rollingVec[i] = nullptr;
						}
					}

					for (int i = 0; i < rollingItem.size(); ++i)
					{
						GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(rollingItem[i]);
					}
					rollingItem.clear();

					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					m_pTex = NULL;
				}
			}
		}).detach();
}




