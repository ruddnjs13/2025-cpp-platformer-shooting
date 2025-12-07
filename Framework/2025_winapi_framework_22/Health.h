#pragma once
#include "Component.h"
#include "MyAction.h"

class Health
	: public Component
{
public:
	Health();
	~Health();
public:
	MyAction<int> OnHealthChanged;
	void Init() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void SetHealth(int health) { m_health = health; }
	void TakeDamage(int damage);
	bool IsDead() const { return m_isDead; }
private:
	int m_health;
	bool m_isDead = false;
};

