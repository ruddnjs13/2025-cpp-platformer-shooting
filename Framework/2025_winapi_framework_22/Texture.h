#pragma once
#include "ResourceBase.h"
class Texture :
    public ResourceBase
{
public:
    Texture();
    ~Texture();
public:
    LONG GetWidth() const { return m_bitInfo.bmWidth; }
    LONG GetHeight() const { return m_bitInfo.bmHeight; }
    HDC& GetTextureDC(const double angle = 0.f);
public:
    void Load(const wstring& _filePath);
private:
    HBITMAP m_hBit;    
    HDC     m_hDC;
	HDC     m_rotHDC;
    BITMAP  m_bitInfo;
};

