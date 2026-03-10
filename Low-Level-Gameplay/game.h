#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

class Game 
{
	// SCREEN
	sf::Vector2u screenSize;

	Behaviour* player;

public:
	void Start(sf::Vector2u screenSize);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};