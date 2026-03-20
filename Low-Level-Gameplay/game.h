#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "collisions.h"
#include <vector>

class Game 
{
	// SCREEN
	sf::Vector2u screenSize;

	Behaviour* player;

	sf::Texture* background;
	sf::Sprite* backgroundSprite;

	std::vector<Collider*> collisions;

public:
	Game(sf::Vector2u screenSize);
	~Game();

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};