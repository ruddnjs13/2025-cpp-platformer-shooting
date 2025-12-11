#include "pch.h"
#include "SlotReel.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TestWeapon.h"
#include "RollingItem.h"
#include "TestWeapon2.h"
#include "Nailgun.h"
#include "RazerGun.h"
#include "PizzeGun.h"
#include "Rocket.h"
#include "Bazuka.h"
#include "Sniper.h"
#include "TurnManager.h"
#include "SceneManager.h"
#include "Collider.h"
#include "WeaponHolderComponent.h"
#include <math.h>

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
}

SlotReel::~SlotReel()
{
	m_pWeaponHolder->DestroyWeapon();
}

void SlotReel::WeaponFliper(bool isFlip, int playerCount)
{
	if (m_pWeaponHolder->GetCurrentWeapon())
	{
		m_pWeaponHolder->GetCurrentWeapon()->SetFliper(isFlip, playerCount);
	}
}


void SlotReel::Render(HDC _hdc)
{
	if (m_pTex)
	{
		Vec2 pos = GetPos();
		Vec2 size = GetSize();
		LONG width = m_pTex->GetWidth();
		LONG height = m_pTex->GetHeight();

		::TransparentBlt(_hdc,
			(int)(pos.x - size.x / 2),
			(int)(pos.y - size.y / 2),
			size.x,
			size.y,
			m_pTex->GetTextureDC(),
			0, 0, width, height,
			RGB(255, 0, 255));
	}
}

void SlotReel::SetRollingTexture(RollingItem* rollItem, wstring textureName, Vec2 offsetPos, float speed)
{
	rollItem->SetSize({ 125,125 });
	rollItem->SetPos(offsetPos);
	rollItem->SetTexture(textureName);
	rollItem->SetDownSpeed(speed);
}

void SlotReel::SetStartTexture(RollingItem* rollItem, wstring textureName, Vec2 offsetPos)
{
	rollItem->SetSize({ 125,125 });
	rollItem->SetPos(offsetPos);
	rollItem->SetTexture(textureName);
}

void SlotReel::MakeWeapon(Weapon* targetWeapon, int _playerNum, Vec2 weaponSize)
{
	m_pWeaponHolder->SetOwner(GetOwner());
	Vec2 pos = GetOwner()->GetPos();
	pos.y -= GetOwner()->GetSize().y / 2.f;
	pos.x += 10.f;

	m_pWeaponHolder->ChangeWeapon(targetWeapon, pos, weaponSize, _playerNum);
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(m_pWeaponHolder->GetCurrentWeapon(), Layer::Weapon);
}

void SlotReel::DestroyWeapon()
{
	isDestory = true;
	GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Waiting);
}
void SlotReel::Update()
{
	if (isRunning)
	{
		m_waitTime += fDT;
		SlotRolling();
	}

	if (isDestory)
	{
		m_destoryTime += fDT;

		if (m_destoryTime >= 2)
		{
			m_pWeaponHolder->DestroyWeapon();
		}
	}
}

void SlotReel::EnterCollision(Collider* _other) {}
void SlotReel::StayCollision(Collider* _other) {}
void SlotReel::ExitCollision(Collider* _other) {}

void SlotReel::SlotRolling()
{
	if (!isRunning)
		return;

	if (m_rollingCnt >= 11)
	{
		isRunning = false;
		m_rollingCnt = 0;
		return;
	}

	if (m_waitTime >= m_maxWaitTime)
	{
		isRunning = false;
		m_waitTime = 0;
		m_rollingCnt++;

		Vec2 offsetPoss = GetPos();
		offsetPoss.y -= 60;
		int playerNum = GetPlayerNum();

		vector<RollingItem*> rollingItem;

		if (m_rollingCnt == 10)
			m_maxWaitTime = 10;

		if (m_rollingCnt == 9)
			speed = 0;

		if (rollingVec.size() < 3)
			rollingVec.resize(3, nullptr);

		rollingItem.push_back(rollingVec[0]);
		rollingVec[0] = rollingVec[1];
		rollingVec[1] = rollingVec[2];

		for (int i = 0; i < 2; ++i)
		{
			if (rollingVec[i])
				rollingVec[i]->SetDownSpeed(speed);
		}

		RollingItem* rollingItems = new RollingItem;

		int randomTexture = rand() % 8 + 1;
		if (m_rollingCnt == 8)
			storeValue = randomTexture;


		PLAY_SOUND(L"SlotMachineSFX");
		switch (randomTexture)
		{
		case 1: SetRollingTexture(rollingItems, L"Gun1", offsetPoss, speed); break;
		case 2: SetRollingTexture(rollingItems, L"AK47", offsetPoss, speed); break;
		case 3: SetRollingTexture(rollingItems, L"Bazooka", offsetPoss, speed); break;
		case 4: SetRollingTexture(rollingItems, L"Rocket", offsetPoss, speed); break;
		case 5: SetRollingTexture(rollingItems, L"RazerGun", offsetPoss, speed); break;
		case 6: SetRollingTexture(rollingItems, L"PizzaGun", offsetPoss, speed); break;
		case 7: SetRollingTexture(rollingItems, L"NailGun", offsetPoss, speed); break;
		case 8: SetRollingTexture(rollingItems, L"Sniper", offsetPoss, speed); break;
		}

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(rollingItems, Layer::RollItem);

		rollingVec[2] = rollingItems;

		if (m_rollingCnt == 10)
		{
			GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::EFFECT);
			switch (storeValue)
			{
			case 1: MakeWeapon(new TestWeapon2, playerNum, { 40,40 }); break;
			case 2: MakeWeapon(new TestWeapon, playerNum, { 40,40 }); break;
			case 3: MakeWeapon(new Bazuka, playerNum, { 40,40 }); break;
			case 4: MakeWeapon(new Rocket, playerNum, { 45,45 }); break;
			case 5: MakeWeapon(new RazerGun, playerNum, { 30,30 }); break;
			case 6: MakeWeapon(new PizzeGun, playerNum, { 20,20 }); break;
			case 7: MakeWeapon(new Nailgun, playerNum, { 20,20 }); break;
			case 8: MakeWeapon(new Sniper, playerNum, { 50,50 }); break;
			}

			for (int i = 0; i < 3; ++i)
			{
				if (rollingVec[i])
				{
					GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(rollingVec[i]);
					rollingVec[i] = nullptr;
				}
			}

			for (auto item : rollingItem)
			{
				GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(item);
			}

			rollingVec.clear();
			rollingVec.resize(3, nullptr); 
			rollingItem.clear();

			GET_SINGLE(TurnManager)->ChangeTurn(TurnType::Play);
			m_pTex = nullptr;
		}

		isRunning = true;
	}
}

void SlotReel::SetSlotRolling(int _playerNum)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Slot");

	rollingVec.clear();
	rollingVec.resize(3, nullptr); 

	Vec2 offsetPos = GetPos();

	for (int i = 0; i < 3; i++)
	{
		int randoCnt = rand() % 3 + 1;
		RollingItem* rollingItem = new RollingItem;

		switch (randoCnt)
		{
		case 1: SetStartTexture(rollingItem, L"Gun1", offsetPos); break;
		case 2: SetStartTexture(rollingItem, L"AK47", offsetPos); break;
		case 3: SetStartTexture(rollingItem, L"RazerGun", offsetPos); break;
		}

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(rollingItem, Layer::DEFAULT);
		offsetPos.y -= 30;
		rollingVec.push_back(rollingItem);
	}

	speed = 150.f;
	m_rollingCnt = 0;
	m_maxWaitTime = 0.4f;
	m_waitTime = 0;
	storeValue = 0;
	SetPlayerNum(_playerNum);
	isRunning = true;
	isDestory = false;
}
