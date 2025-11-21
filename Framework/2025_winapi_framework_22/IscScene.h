#pragma once
#include "Scene.h"
class IscScene :
    public Scene
{
public:
	void Init() override;
	void Update() override;
};

