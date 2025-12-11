#pragma once
#include "Object.h"
#include <wtypes.h>

class Texture;
class Bomb :
    public Object
{
public:
    Bomb();
	~Bomb();

public:
	void Update() override;
	void Render(HDC _hdc) override;
	void EnterCollision(Collider* _other)override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
private:
	void FadeOut();
private:
	float fadeTime = 0.f;
	float damage = 0.f;
	Texture* m_pTex = nullptr;


};

