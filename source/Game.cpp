#include "Game.h"

#include <iostream>
#include <memory>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "EventManager.h"
#include "FrameManager.h"
#include "ObjectManager.h"
#include "PlayerShip.h"

// Temporary hardcoded loading:
sf::Image icon;
sf::Texture texture;
sf::Music music;
sf::RenderWindow* window;
sf::Sprite* sprite;

void Game::Initialize()
{
	// Set up managers

	// Create the main window
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML window");

	// Set the Icon
	if (!icon.loadFromFile("assets/icon.png")) {
		throw new std::exception("Unable to load assets/icon.png");
	}
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Load a sprite to display
	if (!texture.loadFromFile("assets/cute_image.jpg")) {
		throw new std::exception("Unable to load assets/image.jpg");
	}
	sprite = new sf::Sprite(texture);

	// Load a music to play
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
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			/////// TODO: Call InputManager !!! ///////////////
			// Close window: exit
			if (event.type == sf::Event::Closed) {
				window->close();
			}

			// Escape pressed: exit
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window->close();
			}
			/////////////////////////////////////////////////////////////////////
		}
		// Clear screen
		window->clear();

		// Draw the sprite
		window->draw(*sprite);

		// Manager updates...
		EventManager::Update(*window);
		FrameManager::Update(*window);
		ObjectManager::Update(*window);

		// Update the window
		window->display();
	}

	Game::Stop();
}

void Game::Stop()
{
	delete window;
	delete sprite;
}