#pragma once
#include "player.h"

class Collider
{
protected:
	sf::Vector2u screenSize;
public:
	Collider(sf::Vector2u screen);
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual bool Collision(Behaviour* behaviour) = 0;
};

class Block : public Collider 
{
private:
	sf::RectangleShape box;
	float x, y;
	float w = 100.0f, h = 100.0f;
public:
	Block(sf::Vector2u screen, float x, float y, float w = 100.0f, float h = 100.0f);
	bool Collision(Behaviour* behaviour) override;
	void Render(sf::RenderWindow* window) override;
};

class ScreenBounds : public Collider 
{
	sf::Texture* border;
	sf::Sprite* sprite;

	int borderSize = 23;

public:
	ScreenBounds(sf::Vector2u screen);
private:
	~ScreenBounds();

public:
	bool Collision(Behaviour* behaviour) override;
	void Render(sf::RenderWindow* window) override;
	
};