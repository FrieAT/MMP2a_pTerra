/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

class IQuadrantObserver
{
public:
    ~IQuadrantObserver() { }
    virtual void OnQuadrantUpdate(std::string strEvent) = 0;
};