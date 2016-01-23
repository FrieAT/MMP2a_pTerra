/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"
#include "IFrameObserver.h"

class IDrawing : public IComponent
{
public:
    virtual ~IDrawing() { }
	virtual void Draw(sf::RenderWindow* pWindow) = 0;
    virtual void Update() = 0;
	virtual void SetScale(sf::Vector2f ScaleToSize) { return; }
    virtual void SetTextureArea(sf::FloatRect Area) = 0;
    virtual void SetText(std::string strText) { }
    virtual sf::FloatRect GetTextureArea() = 0;
	
    EComponentType GetComponentType()
	{
		return EComponentType::Drawing;
	}
    virtual std::string GetComponentName() { return std::string("IDrawing"); }

private:

};
