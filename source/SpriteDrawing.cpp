/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "SpriteDrawing.h"
#include "GameObject.h"
#include "IPosition.h"
#include "TextureFactory.h"
#include "Game.h"

SpriteDrawing::SpriteDrawing(std::string strRessourcePath)
: m_strResPath(strRessourcePath)
, m_ScaleToSize(sf::Vector2f(0.f, 0.f))
, m_iTextureRectsCount(0)
, m_iTextureFrameUpdateCount(Game::m_iFrameRate)
, m_iCurrentFrameCount(0)
{
    m_pTexture = TextureFactory::GetInstance().GetTexture(strRessourcePath);
	m_pSprite = new sf::Sprite(*m_pTexture);
}

SpriteDrawing::SpriteDrawing(std::string strRessourcePath, sf::Vector2f ScaleToSize) : SpriteDrawing(strRessourcePath)
{
    m_ScaleToSize = ScaleToSize;
    
	SetScale(ScaleToSize);
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
    
    int iTextureAreasSize = m_TextureRects.size();
    if(iTextureAreasSize > 1 && m_iCurrentFrameCount++ >= m_iTextureFrameUpdateCount)
    {
        m_iCurrentFrameCount = 0;
        m_iTextureRectsCount++;
    }
	if (m_iTextureRectsCount >= iTextureAreasSize)
	{
		m_iTextureRectsCount = 0;
	}
    if(iTextureAreasSize > 0)
    {
        m_pSprite->setTextureRect(m_TextureRects[m_iTextureRectsCount]);
    }
}

void SpriteDrawing::Draw(sf::RenderWindow* pWindow)
{
	Update();
	pWindow->draw(*m_pSprite);
}

void SpriteDrawing::SetScale(sf::Vector2f ScaleToSize)
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

sf::FloatRect SpriteDrawing::GetTextureArea()
{
    // TODO: Possible implementation to access explicit TextureRectArea.
    return sf::FloatRect(m_pSprite->getTextureRect());
}

void SpriteDrawing::SetTextureArea(sf::FloatRect Area)
{
    m_TextureRects.push_back(sf::IntRect(Area));
}

void SpriteDrawing::GenerateTextureAreas(int iAmountInX, int iAmountInY)
{
    m_TextureRects.clear(); // Clear existing Texture-Area´s
    if(iAmountInX == 0 || iAmountInY == 0)
    {
        return;
    }
    sf::Vector2u TextureSize = m_pTexture->getSize();
    sf::Vector2u AssetSize(TextureSize.x / iAmountInX, TextureSize.y / iAmountInY);
    for(int y = 0; y < iAmountInY; y++)
    {
        for(int x = 0; x < iAmountInX; x++)
        {
			float fLeft = static_cast<float>(x * AssetSize.x);
			float fTop = static_cast<float>(y * AssetSize.y);
			float fWidth = static_cast<float>(AssetSize.x);
			float fHeight = static_cast<float>(AssetSize.y);
            SetTextureArea(sf::FloatRect(fLeft, fTop, fWidth, fHeight));
        }
    }
}

void SpriteDrawing::Serialize(SerializeNode *pParentNode)
{
    this->IDrawing::Serialize(pParentNode);
    pParentNode->AddElement(new SerializeNode("ResourcePath", ESerializeNodeType::Property, m_strResPath));
    pParentNode->AddElement(new SerializeNode("ResizeToX", ESerializeNodeType::Property, std::to_string(m_ScaleToSize.x)));
    pParentNode->AddElement(new SerializeNode("ResizeToY", ESerializeNodeType::Property, std::to_string(m_ScaleToSize.y)));
    SerializeNode* pTextureRects = new SerializeNode("TextureAreaRects", ESerializeNodeType::List);
    auto it = m_TextureRects.begin();
    unsigned int iCount = 0;
    while(it != m_TextureRects.end())
    {
        SerializeNode* pTextureRect = new SerializeNode(std::to_string(iCount), ESerializeNodeType::List);
        pTextureRect->AddElement(new SerializeNode("Left", ESerializeNodeType::Property, std::to_string(it->left)));
        pTextureRect->AddElement(new SerializeNode("Top", ESerializeNodeType::Property, std::to_string(it->top)));
        pTextureRect->AddElement(new SerializeNode("Width", ESerializeNodeType::Property, std::to_string(it->width)));
        pTextureRect->AddElement(new SerializeNode("Height", ESerializeNodeType::Property, std::to_string(it->height)));
        pTextureRects->AddElement(pTextureRect);
        it++;
        iCount++;
    }
    pParentNode->AddElement(pTextureRects);
    pParentNode->AddElement(new SerializeNode("TextureRectsCount", ESerializeNodeType::Property, std::to_string(m_iTextureRectsCount)));
    pParentNode->AddElement(new SerializeNode("CurrentFrameCount", ESerializeNodeType::Property, std::to_string(m_iCurrentFrameCount)));
    pParentNode->AddElement(new SerializeNode("TextureFrameUpdateCount", ESerializeNodeType::Property, std::to_string(m_iTextureFrameUpdateCount)));
}

IComponent* SpriteDrawing::Deserialize(SerializeNode *pNode)
{
    std::string strResPath = (pNode->GetNode("ResourcePath"))->GetValue();
    sf::Vector2f ResizeToSize(stof((pNode->GetNode("ResizeToX"))->GetValue()), stof((pNode->GetNode("ResizeToY"))->GetValue()));
    
    SpriteDrawing* pComponent = new SpriteDrawing(strResPath, ResizeToSize);
    
    SerializeNode* pNodeRects = pNode->GetNode("TextureAreaRects");
    int iCount = 0;
    SerializeNode* pCurrentRectNode = pNodeRects->GetNode(iCount++);
    while(pCurrentRectNode != nullptr)
    {
        int iLeft = stoi((pCurrentRectNode->GetNode("Left"))->GetValue());
        int iTop = stoi((pCurrentRectNode->GetNode("Top"))->GetValue());
        int iWidth = stoi((pCurrentRectNode->GetNode("Width"))->GetValue());
        int iHeight = stoi((pCurrentRectNode->GetNode("Height"))->GetValue());
        
        pComponent->m_TextureRects.push_back(sf::IntRect(iLeft, iTop, iWidth, iHeight));
        
        pCurrentRectNode = pNodeRects->GetNode(iCount++);
    }
    
    pComponent->m_iTextureRectsCount = stoi((pNode->GetNode("TextureRectsCount"))->GetValue());
    pComponent->m_iCurrentFrameCount = stoi((pNode->GetNode("CurrentFrameCount"))->GetValue());
    pComponent->m_iTextureFrameUpdateCount = stoi((pNode->GetNode("TextureFrameUpdateCount"))->GetValue());
    
    return pComponent;
}