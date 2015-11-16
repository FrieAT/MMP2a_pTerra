
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "EventManager.h"
#include "FrameManager.h"
#include "ObjectManager.h"


#include "PlayerShip.h"

int main(int argc, char const** argv)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("assets/icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("assets/cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("assets/nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();
    
    ObjectManager::AddGameObject(*new PlayerShip());
    
    // Start the game loop
    while (window.isOpen())
    {
        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);
        
        // Manager updates...
        EventManager::Update(window);
        FrameManager::Update(window);
        ObjectManager::Update(window);
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
