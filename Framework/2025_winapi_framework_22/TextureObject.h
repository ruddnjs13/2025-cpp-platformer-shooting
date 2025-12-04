#pragma once
#include "Object.h"


class Texture;

class TextureObject :
	public Object
{
public:
	TextureObject();
	~TextureObject();

public:
	void Update() override;
	void Render(HDC _hdc) override;
	void LateUpdate() override;
	void Rotate();

public:
	void SetOffset(Vec2 newOffset) { m_offsetPos = newOffset; }
	Vec2 GetOffset() { return m_offsetPos; }
	Object* GetOwner() { return m_owner; }
	void SetOwner(Object* owner) { m_owner = owner; }
	void SetAngleValue(float angle) { m_angleValue = angle; }
	
private:
	float m_angleValue = 0;
	Object* m_owner;
	Vec2 m_offsetPos;
	Texture* m_pTex;
};

