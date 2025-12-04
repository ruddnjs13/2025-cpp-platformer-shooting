#pragma once
#include "Object.h"

class Texture;

class Background
 	: public Object
{
private:
	Texture* m_Texture;
public:
	void Init(Texture* texture);
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;
};

