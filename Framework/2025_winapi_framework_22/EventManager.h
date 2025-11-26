#pragma once
class MyAction;

class EventManager
{
	DECLARE_SINGLE(EventManager)
private :
	std::unordered_map<EvtType, MyAction> map;
public:
	void Init();
	void Update();
	void Invoke(EvtType evtType);
};

	