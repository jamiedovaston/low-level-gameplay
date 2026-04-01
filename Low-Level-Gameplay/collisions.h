#pragma once
#include "entity.h"

class Collider
{
protected:
	sf::Vector2f originPoint;
public:
	Collider(sf::Vector2f originPoint);
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual bool Collision(Entity* behaviour) = 0;
};

class Block : public Collider 
{
	sf::Texture* block;
	sf::Sprite* sprite;

	float x, y;
	float w = 100.0f, h = 100.0f;

public:
	Block(sf::Vector2f originPoint, float x, float y, float w = 100.0f, float h = 100.0f);
private:
	~Block();

public:
	bool Collision(Entity* behaviour) override;
	void Render(sf::RenderWindow* window) override;
};

class ScreenBounds : public Collider 
{
	sf::Texture* border;
	sf::Sprite* sprite;

	sf::Vector2i levelSize = sf::Vector2i(630, 720); // DEFAULT SCREEN SIZE

	int borderSize = 23; //px

public:
	ScreenBounds(sf::Vector2f originPoint);
private:
	~ScreenBounds();

public:
	bool Collision(Entity* behaviour) override;
	void Render(sf::RenderWindow* window) override;
	
};