#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class Entity
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
	Entity(sf::Vector2u screen);
	~Entity();

public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
};

class Player : public Entity
{
	// INPUT PRESSED DOWN
	std::map<sf::Keyboard::Key, bool> is_pressed;

	float jumpSpeed = 1000.0f, horizontalSpeed = 1.4f;
	float maxVerticalSpeed = 500.0f, maxHorizontalSpeed = 400.0f;
	float gravity = -.15f;
	float drag = .995f;

	// ANIMATIONS
	float inpDirectionX = 0.0f;
	float previousDirectionX = 0.0f;
	float elapsedTime = 0.0f;
	int frame = 1;

public:
	bool freeze = false;

	Player(sf::Vector2u screen);
	~Player();

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;

	void Animations(float deltaTime);
};

class Enemy : public Entity 
{
public:
	Enemy(sf::Vector2u screen);
	~Enemy();

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
};