#include "pch.h"
#include "UIManager.h"
#include "TitleCanvas.h"
#include "InGameCanvas.h"

void UIManager::Init()
{
	m_curCanvas = nullptr;

	RegisterCanvas(CanvasType::InGame, std::make_shared<InGameCanvas>());
	RegisterCanvas(CanvasType::Title, std::make_shared<TitleCanvas>());
}

void UIManager::Update()
{
	if (m_curCanvas == nullptr)
		return;
	m_curCanvas->Update();
}

void UIManager::Render(HDC _hdc)
{
	if (m_curCanvas == nullptr)
		return;
	m_curCanvas->Render(_hdc);
}

void UIManager::RegisterCanvas(const CanvasType canvasType, std::shared_ptr<Canvas> canvas)
{
	if (canvas == NULL)
		return;
	m_mapCanvas.insert({canvasType, canvas});
}

void UIManager::SetCanvas(const CanvasType canvasType)
{
	if (m_curCanvas != nullptr)
	{
		m_curCanvas->Release();
		m_curCanvas = nullptr;
	}

	auto iter = m_mapCanvas.find(canvasType);
	if (iter != m_mapCanvas.end())
	{
		m_curCanvas = iter->second;
		m_curCanvas->Init();
	}
}
