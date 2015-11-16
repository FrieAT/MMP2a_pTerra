//
//  SpriteDrawing.cpp
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 14.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#include "SpriteDrawing.h"
#include "GameObject.h"
#include "IPosition.h"

SpriteDrawing::SpriteDrawing(sf::Sprite &Sprite, sf::Texture &Texture)
{
    this->Sprite = &Sprite;
    this->Texture = &Texture;
}

void SpriteDrawing::Update()
{
    std::shared_ptr<IPosition> PositionComponent = std::static_pointer_cast<IPosition>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    if(PositionComponent != nullptr) {
        Sprite->setPosition((PositionComponent->GetPosition()));
    }
}

void SpriteDrawing::Draw(sf::RenderWindow &window)
{
    Update();
    window.draw(*Sprite);
}