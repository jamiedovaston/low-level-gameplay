#pragma once
#include <SFML/Graphics.hpp>
#include <map>

// ABSTRACT CLASS COULD BECOME 'ENTITY'
class Behaviour
{
public:
	// SCREEN
	sf::Vector2u screenSize;

	Behaviour(sf::Vector2u screen);
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
};

class Player : public Behaviour
{
	// PLAYER
	sf::CircleShape player;
	float radius = 25.0f;

	sf::Vector2f position;
	sf::Vector2f velocity;

	// INPUT PRESSED DOWN
	std::map<sf::Keyboard::Key, bool> is_pressed;

	float verticalSpeed = .8f, horizontalSpeed = .4f;
	float maxVerticalSpeed = 100.0f, maxHorizontalSpeed = 200.0f;
	float jumpSpeed = 30.0f;
	float gravity = -.45f;
	float drag = .9995f;

	// TEST BOX
	sf::RectangleShape box;
	float x = 100.0f, y = 200.0f;
	float w = 100.0f, h = 100.0f;
	
public:
	bool freeze = false;

	Player(sf::Vector2u screen);
	void Start() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;

private:
	void ScreenBoundsCollision();
	bool CollisionBoxTest();
};