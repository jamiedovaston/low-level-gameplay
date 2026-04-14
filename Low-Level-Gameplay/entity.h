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
	sf::Sprite* sprite = nullptr;

	// POSITION = OFFSET | SIZE = ORIGINAL SPRITE SIZE
	sf::FloatRect spriteRect = sf::FloatRect(sf::Vector2f(28.0f / 2.0f, 25.0f), sf::Vector2f(37.0f / 2.0f, 43.0f / 2.0f)); // TEMP PLAYER

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f projectedVelocity;

	sf::Vector2f direction = sf::Vector2f(0.0f, 0.0f);
	
	bool isGrounded = false;
	float maxVerticalSpeed = 500.0f, maxHorizontalSpeed = 400.0f;
	float groundedBuffer = 0.0f;
	float gravity = -.15f;
	float drag = .995f;

	bool isDead = false;
	bool freeze = false;
public:
	Entity(sf::Vector2u screen);
	~Entity();

public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;

	virtual void Hit() = 0;
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

public:

	Player(sf::Vector2u screen);
	~Player();

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;

	void Hit() override;

	void Movement(float deltaTime);
	void Animations(float deltaTime);
};

class Enemy : public Entity 
{
protected:
	Player* player;

	// ANIMATIONS
protected:
	float elapsedTime = 0.0f;
	int frame = 1;
public:
	enum Enemy_Flags {
		NONE = 0,
		TRANSFORM,
		KILL
	} flags = Enemy_Flags::NONE;

	Enemy(Player* player, sf::Vector2u screen);
	~Enemy();

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
	void Hit() override;

	virtual void Animations(float deltaTime) = 0;
};

class Skeleton : public Enemy
{
	bool isGroundedChanged = false;

	int directionChangeCount = 3;
public:
	Skeleton(Player* player, sf::Vector2u screen);
	~Skeleton();

	void Update(float deltaTime) override;
	void Animations(float deltaTime) override;

	void ChangeDirection(sf::Vector2f direction);
};

class Club : public Enemy 
{
public:
	Club(Player* player, sf::Vector2u screen);
	~Club();

	void Update(float deltaTime) override;
	void Animations(float deltaTime) override;
};