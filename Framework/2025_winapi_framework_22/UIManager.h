#pragma once
#include "Canvas.h"
#include "Enums.h"

class UIManager
{
	DECLARE_SINGLE(UIManager)
public:
	void Init();
	void Update();
	void Render(HDC _hdc);

public:
	void RegisterCanvas(const CanvasType canvasType, std::shared_ptr<Canvas> canvas);
	void SetCanvas(const CanvasType canvasType);

public:
	const std::shared_ptr<const Canvas>& GetCurCanvas() const
	{
		return m_curCanvas;
	}
private:
	std::shared_ptr<Canvas> m_curCanvas;
	std::unordered_map<CanvasType, std::shared_ptr<Canvas>> m_mapCanvas;
};

