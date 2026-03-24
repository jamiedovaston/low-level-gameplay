#pragma once
#include <SFML/Graphics.hpp>
#include <map>

// ABSTRACT CLASS COULD BECOME 'ENTITY'
class Behaviour
{
public:
	bool isGrounded = false;
	float groundedBuffer = 0.0f;

	// SCREEN
	sf::Vector2u screenSize;
	int borderSize = 23; // px

	// ENTITY
	sf::Vector2i spriteSize;
	sf::Texture* texture = nullptr;
	sf::Sprite* sprite = nullptr;

	// POSITION = OFFSET | SIZE = ORIGINAL SPRITE SIZE
	sf::FloatRect spriteRect = sf::FloatRect(sf::Vector2f(28.0f / 2.0f, 25.0f), sf::Vector2f(37.0f / 2.0f, 43.0f / 2.0f)); // TEMP PLAYER

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f projectedVelocity;

public:
	Behaviour(sf::Vector2u screen);
	~Behaviour();

public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
};