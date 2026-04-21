#pragma once
#include "entity.h"

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

class Sphere : public Enemy
{
public:
	Sphere(Player* player, sf::Vector2u screen);
	~Sphere();

	void Update(float deltaTime) override;
	void Animations(float deltaTime) override;
};

class Orb : public Enemy
{
public:
	Orb(Player* player, sf::Vector2u screen);
	~Orb();

	void Update(float deltaTime) override;
	void Animations(float deltaTime) override;
};