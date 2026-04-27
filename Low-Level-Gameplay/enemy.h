#pragma once
#include "entity.h"

class Enemy : public Entity
{
	float runtime;
protected:
	Player* player;
	
private:
	sf::Vector2i coinSize = sf::Vector2i(36, 36);
	sf::Sprite* coin = nullptr;

	// ANIMATIONS
protected:
	float elapsedTime = 0.0f;
	int frame = 1;
public:
	enum Enemy_Flags {
		NONE = 0,
		TRANSFORM,
		POWERUP,
		KILL
	} flags = Enemy_Flags::NONE;

	Enemy(Player* player, sf::Vector2u screen);
	~Enemy();

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;

	virtual void Animations(float deltaTime) = 0;
};

class Skeleton : public Enemy
{
	bool isGroundedChanged = false;

	int directionChangeCount = 3;
public:
	Skeleton(Player* player, sf::Vector2u screen, bool isRight);
	~Skeleton();

	void Update(float deltaTime) override;
	void Animations(float deltaTime) override;

	void ChangeDirection(sf::Vector2f direction);
};

class Club : public Enemy
{
public:
	sf::Vector2f projectedDirection;

	Club(Player* player, sf::Vector2u screen);
	~Club();

	void Update(float deltaTime) override;
	void Animations(float deltaTime) override;
};

class Sphere : public Enemy
{
public:
	float projectedDirection = 0.0f;

	Sphere(Player* player, sf::Vector2u screen);
	~Sphere();

	void Update(float deltaTime) override;
	void Animations(float deltaTime) override;
};

class Orb : public Enemy
{
public:
	float projectedDirection = 0.0f;

	Orb(Player* player, sf::Vector2u screen);
	~Orb();

	void Update(float deltaTime) override;
	void Animations(float deltaTime) override;
};