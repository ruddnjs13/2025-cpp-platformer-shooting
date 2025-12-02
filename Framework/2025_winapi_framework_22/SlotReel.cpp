#include "pch.h"
#include "SlotReel.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TestWeapon.h"
#include <math.h>
#include <thread>

SlotReel::SlotReel()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"AimLine");
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

TestWeapon SlotReel::SlotRolling()
{
    std::thread([this]()
        {
			int randomInt = rand() % 50 + 26;

			cout << randomInt << "ÀÌ¸¸Å­ ¹Ýº¹" << endl;

            for (int i = 0; i < randomInt; ++i)
            {
				int randomInt = rand() % 101 + 100;
                std::this_thread::sleep_for(std::chrono::milliseconds(randomInt));
				cout << randomInt << "ÃÊ µÊ"<< endl;

				int randomTexture = rand() % 3 + 1;

				cout << randomTexture << "¾ê°¡ ¼±ÅÃµÊ";;

				switch (randomTexture)
				{
				case 1:
					m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"AimLine");
					break;
				case 2:
					m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Plane");
					break;
				case 3:
					m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Bullet");
					break;
				}
				if (i == randomInt - 1)
				{
					selectWeapon = new TestWeapon;
				}
				return selectWeapon;
            }
        }).detach();
}



