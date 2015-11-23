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
SpriteDrawing::SpriteDrawing(std::string ressource_path, sf::Vector2f scaleTo)
: SpriteDrawing(ressource_path)
{
    // Get Texture Size
    sf::Vector2f texture_size = static_cast<sf::Vector2f>(Texture->getSize());
    
    // If given scaleTo-size is zero, then dont scale!
    if(scaleTo.x == 0) scaleTo.x = texture_size.x;
    if(scaleTo.y == 0) scaleTo.y = texture_size.y;
    
    // Set scale expects a ratio (Default: 1.f / 1.f)
    Sprite->setScale((scaleTo.x / texture_size.x), (scaleTo.y / texture_size.y));
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
		Sprite->setOrigin(PositionComponent->GetOrigin());
	}
}

void SpriteDrawing::Draw(sf::RenderWindow* window)
{
	Update();
	window->draw(*Sprite);
}