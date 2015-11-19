#include "SpriteDrawing.h"
#include "GameObject.h"
#include "IPosition.h"

SpriteDrawing::SpriteDrawing(std::string ressource_path)
{
    this->Texture = new sf::Texture();
    if(!this->Texture->loadFromFile(ressource_path))
    {
        throw std::exception();
    };
	this->Sprite = new sf::Sprite(*this->Texture);
}

void SpriteDrawing::Update()
{
	std::shared_ptr<IPosition> PositionComponent = std::static_pointer_cast<IPosition>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
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