#pragma once

#include <SFML/Graphics.hpp>

#include "IComponent.h"
#include "IFrameObserver.h"

class IDrawing : public IComponent
{
public:
	virtual void Draw(sf::RenderWindow &window) = 0;
	virtual void Update() = 0;
	EComponentType GetComponentType()
	{
		return EComponentType::Drawing;
	}

private:

};
