#include "pch.h"
#include "Texture.h"
#include "Core.h"
Texture::Texture()
	: m_hBit(nullptr)
	, m_hDC(nullptr)
	, m_rotHDC(nullptr)
	, m_bitInfo{}
{
}

Texture::~Texture()
{
    ::DeleteDC(m_hDC);
    ::DeleteDC(m_rotHDC);
	::DeleteObject(m_hBit);
}

HDC& Texture::GetTextureDC(const double angle)
{
	double rad = angle * (  PI / 180);
    rad *= -1;

    double sinA = std::sin(rad);
    double cosA = std::cos(rad);

    POINT points[4];

    int cx = m_bitInfo.bmWidth / 2;
    int cy = m_bitInfo.bmHeight / 2;

    points[0] = { -cx, -cy };
    points[1] = { cx,-cy };
    points[2] = { -cx, cy };
    points[3] = { cx, cy };


    POINT dPoints[4];

    for (int i = 0; i < 4; ++i)
    {
        dPoints[i].x = (LONG)(points[i].x * cosA - points[i].y * sinA);
        dPoints[i].y = (LONG)(points[i].x * sinA + points[i].y * cosA);
    }

    LONG maxX = dPoints[0].x;
    LONG maxY = dPoints[0].y;
    LONG minX = dPoints[0].x;
    LONG minY = dPoints[0].y;

    for (int i = 0; i < 4; ++i)
    {
        maxX = max(dPoints[i].x, maxX);
        minX = min(dPoints[i].x, minX);
        maxY = max(dPoints[i].y, maxY);
        minY = min(dPoints[i].y, minY);
    }

    HDC memDC = ::CreateCompatibleDC(m_hDC);
    HBITMAP hBit = ::CreateCompatibleBitmap(m_hDC,
        maxX - minX,
        maxY - minY);
    HBITMAP oldBit = (HBITMAP)SelectObject(memDC, hBit);

    ::PatBlt(memDC, 0, 0, maxX - minX, maxY - minY, RGB(255, 0, 255));


    POINT rPoints[3];

    for (int i = 0; i < 4; ++i)
    {
        if (minX < 0)
        {
            dPoints[i].x -= minX;
            maxX = max(dPoints[i].x, maxX);
        }
        if (minY < 0)
        {
            dPoints[i].y -= minY;
            maxY = max(dPoints[i].y, maxY);
        }

        if (i < 3)
        {
            rPoints[i] = dPoints[i];
        }
    }

    if (minX < 0) minX = 0;
    if (minY < 0) minY = 0;



    ::PlgBlt(memDC,
        rPoints, m_hDC,
        0, 0, m_bitInfo.bmWidth, m_bitInfo.bmHeight,
        NULL, 0, 0);
    m_rotHDC = (m_rotHDC == nullptr ? ::CreateCompatibleDC(m_hDC) : m_rotHDC);
    HBITMAP sHBit = ::CreateCompatibleBitmap(m_hDC,
        maxX-minX,
        maxY-minY);
    HBITMAP oldScaleBit = (HBITMAP)SelectObject(m_rotHDC, sHBit);

    ::BitBlt(m_rotHDC,
        ((m_bitInfo.bmWidth - (maxX - minX)) / 2),
        ((m_bitInfo.bmHeight - (maxY - minY)) / 2), 
        maxX - minX, 
        maxY - minY,
        memDC,
        0, 0, SRCCOPY);

    DeleteDC(memDC);
    DeleteObject(hBit);
    DeleteObject(sHBit);
    return m_rotHDC;
}

void Texture::Load(const wstring& _filePath)
{
	// 1. 인스턴스핸들: nullptr - 독립형 리소스
	// 2. 경로
	// 3. 파일형식 - 비트맵인지
	// 4~5. 파일 크기
	// 6. 옵션 플래그
	m_hBit = (HBITMAP)::LoadImage(nullptr, _filePath.c_str(), IMAGE_BITMAP
		, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	::GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

	assert(m_hBit); // 필수1!!!!!!!!@!@!@#$~!@#%$@!#%^#@!%@!#%!@
	m_hDC = ::CreateCompatibleDC(GET_SINGLE(Core)->GetMainDC());
    ::SelectObject(m_hDC, m_hBit);
}
