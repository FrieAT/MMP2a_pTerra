#include "SpriteDrawing.h"
#include "GameObject.h"
#include "IPosition.h"

SpriteDrawing::SpriteDrawing(std::string ressource_path)
{
    Texture = new sf::Texture();
    if(!Texture->loadFromFile(ressource_path))
    {
        throw std::exception();
    };
	Sprite = new sf::Sprite(*Texture);
}

SpriteDrawing::~SpriteDrawing()
{
    delete Sprite;
    delete Texture;
}

void SpriteDrawing::Update()
{
	IPosition* PositionComponent = (IPosition*)(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	if (PositionComponent != nullptr)
	{
		Sprite->setPosition((PositionComponent->GetPosition()));
		Sprite->setRotation((PositionComponent->GetRotation()));
	}
}

void SpriteDrawing::Draw(sf::RenderWindow* window)
{
	Update();
	window->draw(*Sprite);
}