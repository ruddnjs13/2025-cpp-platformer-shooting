#pragma once
#include "Object.h"

class Texture;

class RollingItem
	:public Object
{
public:
	RollingItem();
	~RollingItem();

public:
	void Update() override;
	void Render(HDC _hdc) override;

public:
	void EnterCollision(Collider* _other)override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
	void SetTexture(wstring _textureName);
	void SetDownSpeed(float _speed);
	void SetIsShow(bool _isShow);
private:
	bool isShow = false;
	float speed;
	Texture* m_pTex;
};

