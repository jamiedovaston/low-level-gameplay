#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

class Game 
{
	// SCREEN
	sf::Vector2u screenSize;

	sf::Texture background;
	Behaviour* player;

	sf::Texture* border;
	sf::Sprite* sprite;

public:
	Game(sf::Vector2u screenSize);
	~Game();

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};