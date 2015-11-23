/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "SpriteDrawing.h"
#include "GameObject.h"
#include "IPosition.h"

SpriteDrawing::SpriteDrawing(std::string& strRessourcePath)
{
    m_pTexture = new sf::Texture();
    if(!m_pTexture->loadFromFile(strRessourcePath))
    {
        throw std::exception();
    }
	m_pSprite = new sf::Sprite(*m_pTexture);
}

SpriteDrawing::SpriteDrawing(std::string& strRessourcePath, sf::Vector2f& ScaleToSize) : SpriteDrawing(strRessourcePath)
{
	// Get Texture Size
    sf::Vector2f TextureSize = static_cast<sf::Vector2f>(m_pTexture->getSize());
    
    // If given scaleTo-size is zero, then dont scale!
	if (ScaleToSize.x == 0)
	{
		ScaleToSize.x = TextureSize.x;
	}
	if (ScaleToSize.y == 0)
	{
		ScaleToSize.y = TextureSize.y;
	}
    // Set scale expects a ratio (Default: 1.f / 1.f)
    m_pSprite->setScale((ScaleToSize.x / TextureSize.x), (ScaleToSize.y / TextureSize.y));
}

SpriteDrawing::~SpriteDrawing()
{
    delete m_pSprite;
    delete m_pTexture;
}

void SpriteDrawing::Update()
{
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	if (pPositionComponent != nullptr)
	{
		m_pSprite->setPosition((pPositionComponent->GetPosition()));
		m_pSprite->setRotation((pPositionComponent->GetRotation()));
		m_pSprite->setOrigin(pPositionComponent->GetOrigin());
	}
}

void SpriteDrawing::Draw(sf::RenderWindow* pWindow)
{
	Update();
	pWindow->draw(*m_pSprite);
}