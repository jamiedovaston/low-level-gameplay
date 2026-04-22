#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "level.h"
#include "collisions.h"
#include "pickup.h"

class EntityManager;
class CurrencyManager;

class Game 
{
	sf::Vector2u screen;

	Player* player;
	Level* lvl;

	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<CurrencyManager> currencyManager;

	sf::Font font;
	sf::Text* text;

	float runtime = 0.0f;
	int spawnIncrement = 0;
public:
	Game(sf::Vector2u screenSize);
	~Game();

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
}; 

class EntityManager
{
	sf::Vector2u screen;
	Player* player;
public:
	std::map<Level*, std::vector<Enemy*>> parent;
	std::map<Level*, int> enemySpawnCount;

	EntityManager(Player* player, sf::Vector2u screen);
	~EntityManager();

	void Spawn(Level* lvl, Enemy* enemy, sf::Vector2f location);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Clear(Level* lvl);
};

class CurrencyManager 
{
	sf::Vector2u screen;
	Player* player;
public:
	std::map<Level*, std::vector<Pickup*>> parent;

	CurrencyManager(Player* player, sf::Vector2u screen);
	~CurrencyManager();

	void Spawn(Level* lvl, Pickup* enemy, sf::Vector2f location);

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};