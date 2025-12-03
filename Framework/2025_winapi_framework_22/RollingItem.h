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
	void SetTexture(wstring _textureName);
	void SetDownSpeed(float _speed);

private:
	float speed;
	Texture* m_pTex;
};

