/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "FontDrawing.h"
#include "GameObject.h"
#include "IPosition.h"
#include "TextureFactory.h"

FontDrawing::FontDrawing(std::string strFontPath, std::string strText, int iCharSize)
{
    // Load a font to display
    m_pFont = TextureFactory::GetInstance().GetFont(strFontPath);
    
    // Create Heading
    m_pText = new sf::Text();
    m_pText->setFont(*m_pFont);
    m_pText->setString(strText);
    m_pText->setCharacterSize(iCharSize);
    m_pText->setColor(sf::Color::White);
}

FontDrawing::~FontDrawing()
{
    delete m_pText;
}

void FontDrawing::Update()
{
    
}

void FontDrawing::Draw(sf::RenderWindow* pWindow)
{
    IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    sf::Vector2f Position = pPositionComponent->GetPosition();
    m_pText->setPosition(Position.x, Position.y);
    pWindow->draw(*m_pText);
}

sf::FloatRect FontDrawing::GetTextureArea()
{
    throw std::runtime_error(std::string("NotImplemented: Texture-Area doesn´t exist in sf::Text."));
}

void FontDrawing::SetTextureArea(sf::FloatRect Area)
{
    throw std::runtime_error(std::string("NotImplemented: Texture-Area doesn´t exist in sf::Text."));
}

void FontDrawing::SetText(std::string strText)
{
    m_pText->setString(strText);
}