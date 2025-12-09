#pragma once
class WindManager
{
	DECLARE_SINGLE(WindManager);
public:
	void SetWind(int windPower);

public:
	float m_windPower;
};

