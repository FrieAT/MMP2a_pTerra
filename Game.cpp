#include "Game.h"

#include <iostream>
#include <memory>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "EventManager.h"
#include "FrameManager.h"
#include "ObjectManager.h"
#include "PlayerShip.h"

Game::Game()
{
	// Set up managers

	// Temporary hardcoded loading:
	sf::Image icon;
}

void Game::Initialize()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Set the Icon
	sf::Image icon;
	if (!icon.loadFromFile("assets/icon.png")) {
		throw new std::exception("Unable to load assets/icon.png");
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("assets/cute_image.jpg")) {
		throw new std::exception("Unable to load assets/image.jpg");
	}
	sf::Sprite sprite(texture);

	// Load a music to play
	sf::Music music;
	music.setLoop(true);
	if (!music.openFromFile("assets/nice_music.ogg")) {
		throw new std::exception("Unable to load assets/nice_music.ogg");
	}
}

void Game::Start()
{
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
}

void Game::Stop()
{

}