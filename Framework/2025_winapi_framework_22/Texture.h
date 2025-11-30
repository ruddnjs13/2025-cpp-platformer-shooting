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
    const HDC& GetTextureDC() const { return m_hDC;  }
    HDC& GetRotateTextureDC(const double angle, int sx, int sy, int sw, int sh);
public:
    void Load(const wstring& _filePath);
private:
    HBITMAP m_hBit;    
    HDC     m_hDC;
	HDC     m_rotHDC;
    BITMAP  m_bitInfo;
};

