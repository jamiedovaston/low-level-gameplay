#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include "assetmanagement.h"

class Entity
{
	
public:
	// ENTITY
	sf::Vector2i spriteSize;
	std::unique_ptr<sf::Sprite> sprite = nullptr;
	sf::FloatRect spriteRect; // POSITION = OFFSET | SIZE = ORIGINAL SPRITE SIZE

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f projectedVelocity;

	sf::Vector2f direction = sf::Vector2f(0.0f, 0.0f);
	
	bool isGrounded = false;
	float maxVerticalSpeed = 500.0f, maxHorizontalSpeed = 400.0f;
	float groundedBuffer = 0.0f;
	float gravity = -.15f;
	float drag = .995f;
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

	// ANIMATIONS
	float previousDirectionX = 0.0f;
	float elapsedTime = 0.0f;
	int frame = 1;

	bool canHover = true;
	float glideValue = -45.0f;

public:
	enum FreezeState {
		WIN,
		DEATH,
		WAITING_TO_START
	};

	std::vector<FreezeState> freeze;

public:

	Player(sf::Vector2u screen);
	~Player();

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;

	void Hit();
	void Respawn();

	void Movement(float deltaTime);
	void Animations(float deltaTime);
};