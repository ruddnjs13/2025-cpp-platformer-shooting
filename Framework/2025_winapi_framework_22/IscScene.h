#pragma once
#include "Scene.h"
class IscScene :
    public Scene
{
public:
	IscScene();
	~IscScene();
public:
	void Init() override;
	void Update() override;
};

