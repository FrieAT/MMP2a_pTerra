/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

class LongRect
{
public:
    LongRect(int Left, int Top, int Width, int Height)
    : m_Left(Left)
    , m_Top(Top)
    , m_Width(Width)
    , m_Height(Height)
    {
        
    }
    int m_Left;
    int m_Top;
    int m_Width;
    int m_Height;
};