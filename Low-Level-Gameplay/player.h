#pragma once
#include <SFML/Graphics.hpp>

// ABSTRACT CLASS COULD BECOME 'ENTITY'
class Behaviour
{
public:
	virtual void Start(sf::Vector2u screen) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
};

class Player : public Behaviour
{
	// SCREEN
	sf::Vector2u screenSize;

	// PLAYER
	sf::CircleShape player;
	float radius = 25.0f;

	sf::Vector2f position;
	sf::Vector2f velocity;

	float speed = 0.8f;
	float jumpSpeed = 30.0f;
	float gravity = -.45f;
	
public:
	Player(){}
	void Start(sf::Vector2u screen) override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;

private:
	void ScreenBoundsCollision();
};