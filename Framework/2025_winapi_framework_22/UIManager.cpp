#include "pch.h"
#include "UIManager.h"

void UIManager::Init()
{
	m_curCanvas = nullptr;
}

void UIManager::Update()
{
	if (m_curCanvas == nullptr)
		return;
	m_curCanvas->Update();
}

void UIManager::RegisterCanvas(const CanvasType canvasType, std::shared_ptr<Canvas> canvas)
{
	if (canvas == NULL)
		return;
	m_mapCanvas.insert(m_mapCanvas.end(), {canvasType, canvas});
}

void UIManager::SetCanvas(const CanvasType canvasType)
{
	if (m_curCanvas != nullptr)
	{
		//m_curCanvas->Release();
		m_curCanvas = nullptr;
	}

	auto iter = m_mapCanvas.find(canvasType);
	if (iter != m_mapCanvas.end())
	{
		m_curCanvas = iter->second;
		m_curCanvas->Init();
	}
}
