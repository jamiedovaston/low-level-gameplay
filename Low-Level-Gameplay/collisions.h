#pragma once
#include "enemy.h"
#include "pickup.h"
#include "iostream"
#include "assetmanagement.h"

class Collider
{
protected:
	sf::Vector2f originPoint;
public:
	Collider(sf::Vector2f originPoint);
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual void Collision(Entity* behaviour) = 0;
};

class Block : public Collider 
{
	sf::Sprite* sprite;

protected:
	float x, y;
	float w = 100.0f, h = 100.0f;

public:
	Block(sf::Vector2f originPoint, float x, float y, float w = 100.0f, float h = 100.0f);
	~Block();

public:
	void Collision(Entity* behaviour) override;
	void Render(sf::RenderWindow* window) override;
};

class ScreenBounds : public Collider 
{
	sf::Sprite* sprite;

	sf::Vector2i levelSize = sf::Vector2i(630, 720); // DEFAULT SCREEN SIZE

	int borderSize = 23; //px

public:
	ScreenBounds(sf::Vector2f originPoint);
	~ScreenBounds();

public:
	void Collision(Entity* behaviour) override;
	void Render(sf::RenderWindow* window) override;
	
};

class SpawnPoint : public Block
{
public:
	SpawnPoint(sf::Vector2f originPoint, float x, float y);
	~SpawnPoint();

	void Collision(Entity* behaviour) override;
	void Render(sf::RenderWindow* window) override;

	float Distance(Player* player);
	sf::Vector2f Position();
};