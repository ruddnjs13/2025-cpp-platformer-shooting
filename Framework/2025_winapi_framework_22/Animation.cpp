#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Object.h"
#include "Texture.h"

#undef max;
#undef min;

Animation::Animation()
    : m_owner(nullptr)
    , m_tex(nullptr)
    , m_curFrame(0)
    , m_accTime(0.f)
    , m_mode{}
    , m_loopCount(1)
    , m_speed(1.f)
    , m_finished(false)
{

}

Animation::~Animation()
{

}

void Animation::Create(Texture* _tex, Vec2 _lt, Vec2 _sliceSize,
    Vec2 _step, UINT _frameCount, float _durationPerFrame)
{
    m_tex = _tex;
    if (!_tex || _frameCount <= 0 || _durationPerFrame <= 0.f)
        return;
    m_frames.clear();
    m_frames.reserve(_frameCount);
    for (UINT i = 0; i < _frameCount; ++i)
    {
        // 가독성
        tAnimFrame _fr;
        _fr.vLT = _lt + _step * i;
        _fr.vSlice = _sliceSize;
        _fr.fDuration = _durationPerFrame;
        _fr.vOffset = { 0.f, 0.f };
        m_frames.push_back(_fr);
    }
}

void Animation::ConfigurePlayback(PlayMode _mode, int _loopCount, float _speed)
{
    m_mode = _mode;
    m_loopCount = (_mode == PlayMode::Counted) ? std::max(1, _loopCount) : 1;
    m_speed = _speed;
    m_finished = false;
}

void Animation::ResetToFirstFrame()
{
    m_curFrame = 0;
    m_accTime = 0.f;
    m_finished = false;
}

void Animation::SetFrameOffset(int _index, Vec2 _offset)
{
    if (_index < 0 || _index >= (int)m_frames.size())
        return;
    m_frames[(size_t)_index].vOffset = _offset;
}



void Animation::Update()
{
    if (!m_owner || !m_tex || m_frames.empty() || m_finished)
        return;
    AdvanceFrame();
}

void Animation::AdvanceFrame()
{
    const tAnimFrame& _fr = m_frames[(size_t)m_curFrame];
    m_accTime += fDT * m_speed;

    if (m_accTime >= _fr.fDuration)
    {
        m_accTime -= _fr.fDuration;
        ++m_curFrame;

        if (m_curFrame >= (int)m_frames.size())
        {
            switch (m_mode)
            {
            case PlayMode::Once:
                m_curFrame = (int)m_frames.size() - 1;
                m_finished = true;
                break;
            case PlayMode::Loop:
                m_curFrame = 0;
                break;
            case PlayMode::Counted:
            {
                --m_loopCount;
                if (m_loopCount > 0)
                    m_curFrame = 0;
                else
                {
                    m_curFrame = (int)m_frames.size() - 1;
                    m_finished = true;
                }
            }
            break;
            }
        }
    }
}

void Animation::Render(HDC _hdc)
{
    if (!m_owner || !m_tex || m_frames.empty())
        return;

    Object* obj = m_owner->GetOwner();
    Vec2 pos = obj->GetPos();
    double angle = obj->GetAngle();



    const tAnimFrame& fr = m_frames[(size_t)m_curFrame];
    pos = pos + fr.vOffset;

    // 목적지(화면) 사각형: 스프라이트 중심 정렬
    int dx = (int)(pos.x - fr.vSlice.x / 2);
    int dy = (int)(pos.y - fr.vSlice.y / 2);
    int dw = (int)fr.vSlice.x;
    int dh = (int)fr.vSlice.y;

    // 소스(시트) 사각형
    int sx = (int)fr.vLT.x;
    int sy = (int)fr.vLT.y;
    int sw = (int)fr.vSlice.x;
    int sh = (int)fr.vSlice.y;
    
    double rad = angle * (PI / 180);
    rad *= -1;

    double sinA = std::sin(rad);
    double cosA = std::cos(rad);

    POINT points[4];

    int cx = sw / 2;
    int cy = sh / 2;

    points[0] = { -cx, -cy };
    points[1] = { cx,- cy };
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
        maxX = std::max(dPoints[i].x, maxX);
        minX = std::min(dPoints[i].x, minX);
        maxY = std::max(dPoints[i].y, maxY);
        minY = std::min(dPoints[i].y, minY);
    }

    HDC memDC = ::CreateCompatibleDC(m_tex->GetTextureDC());
    HBITMAP hBit = ::CreateCompatibleBitmap(m_tex->GetTextureDC(),
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
            maxX = std::max(dPoints[i].x, maxX);
        }
        if (minY < 0)
        {
            dPoints[i].y -= minY;
            maxY = std::max(dPoints[i].y, maxY);
        }

        if ( i < 3)
        {
            rPoints[i] = dPoints[i];
        }
    }

    if (minX < 0) minX = 0;
    if (minY < 0) minY = 0;



    ::PlgBlt(memDC,
        rPoints, m_tex->GetTextureDC(),
        sx, sy, sw, sh,
        NULL, 0, 0);
    HDC scaleDC = ::CreateCompatibleDC(m_tex->GetTextureDC());
    HBITMAP sHBit = ::CreateCompatibleBitmap(m_tex->GetTextureDC(), dw, dh);
    HBITMAP oldScaleBit = (HBITMAP)SelectObject(scaleDC, sHBit);

    ::StretchBlt(scaleDC,
        (dw - (maxX - minX)) / 2, (dh - (maxX-minY)) / 2, maxX - minX, maxY - minY,
        memDC,
        0, 0, maxX-minX, maxY-minY, SRCCOPY);



    BOOL debug = ::TransparentBlt(_hdc,
        dx, dy, dw, dh,
        scaleDC,
        0, 0, dw, dh,
        RGB(255, 0, 255));

    DeleteDC(memDC);
    DeleteDC(scaleDC);
    DeleteObject(hBit);
    DeleteObject(sHBit);
    DeleteObject(oldBit);
    DeleteObject(oldScaleBit);
}
