#pragma once
#include <SFML/Graphics.hpp>
#include <map>

// ABSTRACT CLASS COULD BECOME 'ENTITY'
class Behaviour
{
public:
	bool isGrounded = false;

	// SCREEN
	sf::Vector2u screenSize;
	int borderSize = 23; // px

	// ENTITY
	sf::CircleShape sprite;
	float radius = 25.0f;

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f projectedVelocity;

	Behaviour(sf::Vector2u screen);
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
};