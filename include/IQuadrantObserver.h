/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

class IQuadrantObserver
{
public:
    ~IQuadrantObserver() { }
    virtual void OnQuadrantUpdate(std::string strEvent) = 0;
};