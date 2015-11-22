#include "FontDrawing.h"
#include "GameObject.h"
#include "IPosition.h"

FontDrawing::FontDrawing(std::string sFontPath, std::string sText, int iCharSize)
{
    // Load a font to display
    Font = new sf::Font();
    if (!Font->loadFromFile(sFontPath))
    {
        throw new std::runtime_error("Unable to load " + sFontPath);
    }
    
    // Create Heading
    Text = new sf::Text();
    Text->setFont(*Font);
    Text->setString(sText);
    Text->setCharacterSize(iCharSize);
    Text->setColor(sf::Color::White);
}

FontDrawing::~FontDrawing()
{
    delete Text;
    delete Font;
}

void FontDrawing::Update()
{
    
}

void FontDrawing::Draw(sf::RenderWindow* window)
{
    IPosition* PositionComponent = (IPosition*)(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    sf::Vector2f position = PositionComponent->GetPosition();
    Text->setPosition(position.x, position.y);
    window->draw(*Text);
}