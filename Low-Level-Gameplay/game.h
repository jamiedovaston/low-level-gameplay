#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "level.h"
#include "collisions.h"
#include "pickup.h"

class EntityManager;
class PickupManager;
class ScoreManager;

class Game 
{
	sf::Vector2u screen;

	Player* player;
	Level* lvl;

	std::unique_ptr<ScoreManager> scoreManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<PickupManager> currencyManager;

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
	ScoreManager* score;
public:
	enum State {
		NONE,
		POWERUP
	} state;

	std::map<Level*, std::vector<Enemy*>> parent;
	std::map<Level*, int> enemySpawnCount;

	EntityManager(Player* player, sf::Vector2u screen, ScoreManager* score);
	~EntityManager();

	void Spawn(Level* lvl, Enemy* enemy, sf::Vector2f location);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Clear(Level* lvl);
	void ChangeState(State state);
};

class PickupManager 
{
	sf::Vector2u screen;
	Player* player;
	ScoreManager* score;
public:
	std::map<Level*, std::vector<Pickup*>> parent;

	PickupManager(Player* player, sf::Vector2u screen, ScoreManager* score);
	~PickupManager();

	void Spawn(Level* lvl, Pickup* enemy, sf::Vector2f location);

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};

class ScoreManager {
public:
	struct Round {
		bool isPowerUp = false;
		bool isPreviousFused = false;
		int fusedCount;
	};
	
	std::unique_ptr<Round> currentRound;
	int score = 0;

	ScoreManager();
	~ScoreManager();

	Round* NewRound();

	void AddScore(bool isFused);
	void AddScore(int amount);
};