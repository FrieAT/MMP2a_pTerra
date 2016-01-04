/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "SpriteDrawing.h"
#include "GameObject.h"
#include "IPosition.h"
#include "TextureFactory.h"

SpriteDrawing::SpriteDrawing(std::string strRessourcePath)
: m_strResPath(strRessourcePath)
, m_ScaleToSize(sf::Vector2f(0.f, 0.f))
{
    m_pTexture = TextureFactory::GetInstance().GetTexture(strRessourcePath);
	m_pSprite = new sf::Sprite(*m_pTexture);
}

SpriteDrawing::SpriteDrawing(std::string strRessourcePath, sf::Vector2f ScaleToSize) : SpriteDrawing(strRessourcePath)
{
    m_ScaleToSize = ScaleToSize;
    
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

sf::FloatRect SpriteDrawing::GetTextureArea()
{
    return sf::FloatRect(m_pSprite->getTextureRect());
}

void SpriteDrawing::SetTextureArea(sf::FloatRect Area)
{
    m_pSprite->setTextureRect(sf::IntRect(Area));
}

void SpriteDrawing::Serialize(SerializeNode *pParentNode)
{
    this->IDrawing::Serialize(pParentNode);
    pParentNode->AddElement(new SerializeNode("ResourcePath", ESerializeNodeType::Property, m_strResPath));
    pParentNode->AddElement(new SerializeNode("ResizeToX", ESerializeNodeType::Property, std::to_string(m_ScaleToSize.x)));
    pParentNode->AddElement(new SerializeNode("ResizeToY", ESerializeNodeType::Property, std::to_string(m_ScaleToSize.y)));
}

IComponent* SpriteDrawing::Deserialize(SerializeNode *pNode)
{
    std::string strResPath = (pNode->GetNode("ResourcePath"))->GetValue();
    sf::Vector2f ResizeToSize(stof((pNode->GetNode("ResizeToX"))->GetValue()), stof((pNode->GetNode("ResizeToY"))->GetValue()));
    
    SpriteDrawing* pComponent = new SpriteDrawing(strResPath, ResizeToSize);
    
    return pComponent;
}