#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Body 
{
	// SCREEN
	sf::Vector2u screenSize;

	// PLAYER
	sf::CircleShape player;
	float radius = 25.0f;
	sf::Vector2f position;
	float speed = 500.0f;

	// IGNORE
	// float directionX = -1.0f, directionY = -1.0f;

public:
	void Start(sf::Vector2u screenSize);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};