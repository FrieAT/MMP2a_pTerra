/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

class LongRect
{
public:
    LongRect(long Left, long Top, long Width, long Height)
    : m_Left(Left)
    , m_Top(Top)
    , m_Width(Width)
    , m_Height(Height)
    {
        
    }
    long m_Left;
    long m_Top;
    long m_Width;
    long m_Height;
};