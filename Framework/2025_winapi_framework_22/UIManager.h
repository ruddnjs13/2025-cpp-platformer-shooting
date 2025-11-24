#pragma once
#include "Canvas.h"
#include "Enums.h"

class UIManager
{
	DECLARE_SINGLE(UIManager)
public:
	void Init();
	void Update();

public:
	void RegisterCanvas(const CanvasType canvasType, std::shared_ptr<Canvas> canvas);
	void SetCanvas(const CanvasType canvasType);

public:
	const std::shared_ptr<Canvas>& GetCurCanvas() const
	{
		return m_curCanvas;
	}
private:
	//Scene* m_scene;
	std::shared_ptr<Canvas> m_curCanvas;
	std::unordered_map<CanvasType, std::shared_ptr<Canvas>> m_mapCanvas;
};

