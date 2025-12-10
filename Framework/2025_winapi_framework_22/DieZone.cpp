#include "pch.h"
#include "DieZone.h"
#include "Collider.h"

DieZone::DieZone()
{
	auto* col = AddComponent<Collider>();

	col->SetName(L"DieZone");
	col->SetSize({ 4000.f,50.f });
}

DieZone::~DieZone()
{
}

void DieZone::Update()
{
}

void DieZone::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void DieZone::EnterCollision(Collider* _other)
{
}
