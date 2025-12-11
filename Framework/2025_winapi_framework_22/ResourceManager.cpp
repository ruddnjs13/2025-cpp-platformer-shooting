#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
bool ResourceManager::Init()
{
	//fs::path curPath = fs::current_path();
	//m_resourcePath = curPath.parent_path() / L"Output\\build\\Resource\\";

	wchar_t buf[MAX_PATH] = {}; // windows 최대 경로 길이
	::GetModuleFileNameW(nullptr, buf, MAX_PATH); // 현재 실행중인 exe 경로 buf에 저장   
	fs::path exeDir = fs::path(buf).parent_path();                //  buf 전체 경로를 path 객체로 가서 디렉토리만 추출
	fs::path resourceDir = exeDir.parent_path() / L"build" / L"Resource\\"; // release모드일때 build 한번더 붙이는거 무시
	m_resourcePath = resourceDir.native();

	if (!RegisterFontFile(L"Font\\나눔손글씨 암스테르담.ttf"))
		return false;
	RegisterTexture();
	RegisterGDI();

	FMOD::System_Create(&m_pSoundSystem); // 시스템 생성함수
	if (m_pSoundSystem != nullptr)
		m_pSoundSystem->init(64, FMOD_INIT_NORMAL, nullptr);

	RegisterSound();
	return true;
}

void ResourceManager::Release()
{
	// texture delete
	std::unordered_map<wstring, Texture*>::iterator iter;
	for (iter = m_mapTexture.begin(); iter != m_mapTexture.end(); ++iter)
		SAFE_DELETE(iter->second);
	m_mapTexture.clear();

	ReleaseGDI();
	ReleaseFonts();
	std::unordered_map<wstring, SoundInfo*>::iterator iterSound;
	for (iterSound = m_mapSounds.begin(); iterSound != m_mapSounds.end(); ++iterSound)
		SAFE_DELETE(iterSound->second);
	m_mapSounds.clear();

	m_pSoundSystem->close();
	m_pSoundSystem->release();
}

void ResourceManager::RegisterSound()
{
	// 배경음
	LoadSound(L"TitleBGM", L"Sound\\Title_bgm.mp3", true);
	LoadSound(L"Map1BGM", L"Sound\\MapOne_bgm.mp3", true);
	LoadSound(L"Map2BGM", L"Sound\\MapTwo_bgm.mp3", true);
	LoadSound(L"Map3BGM", L"Sound\\MapThree_bgm.mp3", true);

	// 게임 끝
	LoadSound(L"GameEndSFX", L"Sound\\GameEnd_sfx.mp3", false); 

	// 플레이어
	LoadSound(L"PlayerJumpSFX", L"Sound\\PlayerJump_sfx.mp3", false);
	LoadSound(L"PlayerDeadSFX", L"Sound\\PlayerDie_sfx.mp3", false);

	// 무기
	LoadSound(L"AK47FireSFX", L"Sound\\AK47Fire_sfx.mp3", false);
	LoadSound(L"RevolverFireSFX", L"Sound\\RevolverFire_sfx.mp3", false);
	LoadSound(L"BazukaFireSFX", L"Sound\\BazukaFire_sfx.mp3", false);
	LoadSound(L"GrenadeLauncherFireSFX", L"Sound\\GrenadeLauncherFire_sfx.mp3", false);
	LoadSound(L"NailGunFireSFX", L"Sound\\NailGunFire_sfx.mp3", false);
	LoadSound(L"PizzaGunFireSFX", L"Sound\\PizzaGunFire_sfx.mp3", false);
	LoadSound(L"PizzaGunHitSFX", L"Sound\\PizzaGunHit_sfx.mp3", false);
	LoadSound(L"LaserGunFireSFX", L"Sound\\LaserGunFire_sfx.mp3", false);
	LoadSound(L"SniperFireSFX", L"Sound\\SniperFire_sfx.mp3", false);
	LoadSound(L"BulletExplosionSFX", L"Sound\\BulletExplosion_sfx.mp3", false);

	// UI 버튼 클릭
	LoadSound(L"ButtonClickSFX", L"Sound\\ButtonClick_sfx.mp3", false);

	LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	LoadSound(L"BGM", L"Sound\\laserShoot.wav", false);
}

void ResourceManager::FmodUpdate()
{
	if (m_pSoundSystem)
		m_pSoundSystem->update();
}
void ResourceManager::LoadSound(const wstring& _key, const wstring& _path, bool _isLoop)
{
	if (FindSound(_key) || !m_pSoundSystem)
		return;
	wstring strFilePath = m_resourcePath;
	strFilePath += _path;

	// wstring to string
	std::string str;
	str.assign(strFilePath.begin(), strFilePath.end());

	// 루프할지 말지 결정
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력
	if (!_isLoop)
		eMode = FMOD_DEFAULT; // 사운드 1번만 출력
	FMOD::Sound* p = nullptr;

	// BGM면 stream, 아니면 sound
	// 팩토리함수
	//// 사운드 객체를 만드는 것은 system임.
	//						//파일경로,  FMOD_MODE, NULL, &sound
	FMOD_RESULT r = _isLoop
		? m_pSoundSystem->createStream(str.c_str(), eMode, nullptr, &p)
		: m_pSoundSystem->createSound(str.c_str(), eMode, nullptr, &p);

	if (r != FMOD_OK || !p)
		return;

	SoundInfo* pSound = new SoundInfo;
	pSound->IsLoop = _isLoop;
	pSound->pSound = p;
	m_mapSounds.insert({ _key, pSound });

}

void ResourceManager::Play(const wstring& _key)
{
	SoundInfo* pSound = FindSound(_key);
	if (!pSound)
		return;
	SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
	if (!pSound->IsLoop)
		eChannel = SOUND_CHANNEL::EFFECT;
	// 사운드 재생 함수. &channel로 어떤 채널을 통해 재생되는지 포인터 넘김
	m_pSoundSystem->playSound(pSound->pSound, nullptr, false, &m_pChannel[(UINT)eChannel]);

}

void ResourceManager::Stop(SOUND_CHANNEL _channel)
{
	m_pChannel[(UINT)_channel]->stop();
	m_pChannel[(UINT)_channel] = nullptr;

}
void ResourceManager::StopAllSound()
{
	
	for (int i = 0; i < (UINT)SOUND_CHANNEL::END; ++i)
	{
		if (m_pChannel[i])
		{
			m_pChannel[i]->stop();
			m_pChannel[i] = nullptr;
		}
	}
}

void ResourceManager::Volume(SOUND_CHANNEL _channel, float _vol)
{
	// 0.0 ~ 1.0 볼륨 조절
	m_pChannel[(UINT)_channel]->setVolume(_vol);

}

void ResourceManager::Pause(SOUND_CHANNEL _channel, bool _ispause)
{
	m_pChannel[(UINT)_channel]->setPaused(_ispause);
}
SoundInfo* ResourceManager::FindSound(const wstring& _key)
{
	std::unordered_map<wstring, SoundInfo*>::iterator iter = m_mapSounds.find(_key);

	if (iter == m_mapSounds.end())
		return nullptr;
	return iter->second;
}


void ResourceManager::RegisterGDI()
{
	// BRUSH
	m_Brushs[(UINT)BrushType::HOLLOW] = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	m_Brushs[(UINT)BrushType::RED] = (HBRUSH)::CreateSolidBrush(RGB(255, 167, 167));
	m_Brushs[(UINT)BrushType::GREEN] = (HBRUSH)::CreateSolidBrush(RGB(134, 229, 134));

	// PEN 
	m_Pens[(UINT)PenType::RED] = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pens[(UINT)PenType::GREEN] = ::CreatePen(PS_SOLID, 1, RGB(0, 255, 0));

	// 폰트 등록
	RegisterFont(FontType::TITLE, L"나눔손글씨 암스테르담", 0);
}

void ResourceManager::ReleaseGDI()
{
	for (int i = 0; i < (UINT)PenType::END; ++i)
		::DeleteObject(m_Pens[i]);
	for (int i = 1; i < (UINT)BrushType::END; ++i)
		// Hollow 제외하고
		::DeleteObject(m_Brushs[i]);
	for (int i = 0; i < (UINT)FontType::END; ++i)
		::DeleteObject(m_Fonts[i]);
}

bool ResourceManager::RegisterFontFile(const wstring& _path)
{
	wstring fontPath = m_resourcePath;
	fontPath += _path;
	if (!(AddFontResourceExW(fontPath.c_str(), FR_PRIVATE, 0) > 0))
		return false;
	m_vecFontFiles.push_back(fontPath);
	return true;
}

void ResourceManager::ReleaseFonts()
{
	for (const auto& path : m_vecFontFiles)
		::RemoveFontResourceExW(path.c_str(), FR_PRIVATE, 0);
	m_vecFontFiles.clear();
}

void ResourceManager::RegisterFont(FontType _type, const wstring& _name, int _height, int _weight, bool _italic, int _quality)
{

	HFONT h = ::CreateFont(_height, 0, 0, 0, _weight, _italic, false, false, HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, _quality, DEFAULT_PITCH || FF_DONTCARE, _name.c_str());
	m_Fonts[(UINT)_type] = h;
}


void ResourceManager::RegisterTexture()
{
	// texture load
	LoadTexture(L"Plane", L"Texture\\plane.bmp");
	LoadTexture(L"Bullet", L"Texture\\Bullet.bmp");
	LoadTexture(L"Jiwoo", L"Texture\\jiwoo.bmp");
	
	//LoadTexture(L"Background", L"Texture\\background.bmp");
	//LoadTexture(L"Gun1", L"Texture\\Revolver.bmp");
	LoadTexture(L"AimLine", L"Texture\\Aimming.bmp");
	LoadTexture(L"Test2", L"Texture\\RoolRetTest.bmp");
	LoadTexture(L"Slot", L"Texture\\Slot.bmp");

	//총 텍스쳐
	LoadTexture(L"Gun1", L"Texture\\Revolver.bmp");
	LoadTexture(L"AK47", L"Texture\\AK47.bmp");
	LoadTexture(L"Bazooka", L"Texture\\bazooka.bmp");
	LoadTexture(L"Rocket", L"Texture\\Rocket.bmp");
	LoadTexture(L"RazerGun", L"Texture\\RazerGun.bmp");
	LoadTexture(L"PizzaGun", L"Texture\\pizzaBox.bmp");
	LoadTexture(L"NailGun", L"Texture\\NailGun.bmp");
	LoadTexture(L"Sniper", L"Texture\\sniper.bmp");


	//총알 텍스쳐
	LoadTexture(L"Nail", L"Texture\\Nail.bmp");
	LoadTexture(L"Explosion", L"Texture\\Explosion.bmp");
	LoadTexture(L"Bullet1", L"Texture\\Bullet1.bmp");
	LoadTexture(L"BazookaBullet", L"Texture\\Bullet2.bmp");
	LoadTexture(L"RocketBullet", L"Texture\\Bullet3.bmp");
	LoadTexture(L"SniperBullet", L"Texture\\Bullet4.bmp");
	LoadTexture(L"EnergyBullet", L"Texture\\Bullet5.bmp");
	LoadTexture(L"Pizza", L"Texture\\pizza.bmp");

	// 타일맵 텍스쳐
	LoadTexture(L"Ground", L"Texture\\Ground.bmp");
	LoadTexture(L"Grass", L"Texture\\Grass.bmp");
	LoadTexture(L"Trunk_Left", L"Texture\\Trunk_Left.bmp");
	LoadTexture(L"Trunk_Right", L"Texture\\Trunk_Right.bmp");
	LoadTexture(L"Leaves", L"Texture\\Leaves.bmp");
	LoadTexture(L"Background", L"Texture\\Background.bmp");
	LoadTexture(L"Yellow_Ground", L"Texture\\Ground_2.bmp");
	LoadTexture(L"Bridge", L"Texture\\Bridge.bmp");
	LoadTexture(L"Yellow_Grass", L"Texture\\Yellow_Grass.bmp");
	LoadTexture(L"Yellow_Leaves", L"Texture\\Yellow_Leaves.bmp");
	LoadTexture(L"Blue_Grass", L"Texture\\Blue_Grass.bmp");
	LoadTexture(L"Blue_Ground", L"Texture\\Blue_Ground.bmp");

	// ui 텍스쳐
	LoadTexture(L"HpFill", L"Texture\\Hp_Fill.bmp");
	LoadTexture(L"SteminaFill", L"Texture\\SteminaFill.bmp");

	LoadTexture(L"P1_Boarder", L"Texture\\P1_Boarder.bmp");
	LoadTexture(L"P2_Boarder", L"Texture\\P2_Boarder.bmp");

	LoadTexture(L"ExitBtn", L"Texture\\ExitBtn.bmp");
	LoadTexture(L"ExitBtn_Hover", L"Texture\\ExitBtn_Hover.bmp");
	LoadTexture(L"StartBtn", L"Texture\\StartBtn.bmp");
	LoadTexture(L"StartBtn_Hover", L"Texture\\StartBtn_Hover.bmp");
	LoadTexture(L"GuideBtn", L"Texture\\GuideBtn.bmp");
	LoadTexture(L"GuideBtn_Hover", L"Texture\\GuideBtn_Hover.bmp");
	LoadTexture(L"TitleBtn", L"Texture\\TitleBtn.bmp");
	LoadTexture(L"TitleBtn_Hover", L"Texture\\TitleBtn_Hover.bmp");

	LoadTexture(L"One_Red", L"Texture\\One_Red.bmp");
	LoadTexture(L"Two_Red", L"Texture\\Two_Red.bmp");
	LoadTexture(L"One_Blue", L"Texture\\One_Blue.bmp");
	LoadTexture(L"Two_Blue", L"Texture\\Two_Blue.bmp");
	LoadTexture(L"Zero_Red", L"Texture\\Zero_Red.bmp");
	LoadTexture(L"Zero_Blue", L"Texture\\Zero_Blue.bmp");
	LoadTexture(L"Three_Red", L"Texture\\Three_Red.bmp");
	LoadTexture(L"Three_Blue", L"Texture\\Three_Blue.bmp");

	LoadTexture(L"Colon", L"Texture\\Colon.bmp");
	LoadTexture(L"Player1_Win", L"Texture\\Player1Win.bmp");
	LoadTexture(L"Player2_Win", L"Texture\\Player2Win.bmp");
	LoadTexture(L"GameTitle", L"Texture\\GameTitle.bmp");

	// 플레이어 텍스쳐
	LoadTexture(L"Player1", L"Texture\\PlayerOne.bmp");
	LoadTexture(L"Player1Idle", L"Texture\\PlayerOneIdle.bmp");
	LoadTexture(L"Player1Walk", L"Texture\\PlayerOneWalk.bmp");
	LoadTexture(L"Player1Die", L"Texture\\PlayerOneDie.bmp");
	LoadTexture(L"Player2", L"Texture\\PlayerTwo.bmp");
	LoadTexture(L"Player2Idle", L"Texture\\PlayerTwoIdle.bmp");
	LoadTexture(L"Player2Walk", L"Texture\\PlayerTwoWalk.bmp");
	LoadTexture(L"Player2Die", L"Texture\\PlayerTwoDie.bmp");

	//
}

void ResourceManager::LoadTexture(const wstring& _key, const wstring& _path)
{
	Texture* pTex = GetTexture(_key);
	// 찾았으면 리턴
	if (nullptr != pTex)
		return;
	// 처음에 없을거니 경로 찾아서
	wstring texPath = m_resourcePath;
	texPath += _path;

	// 만들어서
	pTex = new Texture;
	pTex->Load(texPath); // 텍스처 자체 로드
	pTex->SetKey(_key); // 키 경로 세팅
	pTex->SetRelativePath(texPath);
	m_mapTexture.insert({ _key,pTex }); // 맵에 저장
}

Texture* ResourceManager::GetTexture(const wstring& _key)
{
	auto iter = m_mapTexture.find(_key);
	if (iter != m_mapTexture.end())
		return iter->second;
	return nullptr;
}


