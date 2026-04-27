#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "level.h"
#include "collisions.h"
#include "pickup.h"
#include <sstream>
#include <iomanip>
#include <cstdlib>

class EntityManager;
class PickupManager;
class ScoreManager;

class Game 
{
	sf::Vector2u screen;

	Player* player;

	std::unique_ptr<Level> lvl;
	// Level* lvl;

	std::unique_ptr<ScoreManager> scoreManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<PickupManager> pickupManager;

	float runtime = 0.0f;
	int spawnIncrement = 0;

	bool loadSceneBuffer = false;
public:
	Game(sf::Vector2u screenSize);
	~Game();

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	void InitialiseNewLevel(std::string filePath);
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
	std::unordered_map<Level*, float> runtime;

	float spawnRate = 3.5f;

	EntityManager(Player* player, sf::Vector2u screen, ScoreManager* score);
	~EntityManager();

	void AssignLevel(Level* lvl);
	void Spawn(Level* lvl, Enemy* enemy, sf::Vector2f location);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Clear(Level* lvl);
};

class PickupManager 
{
	sf::Vector2u screen;
	Player* player;
	ScoreManager* score;

public:
	int bombCount = 0;

	std::map<Level*, std::vector<Pickup*>> parent;

	PickupManager(Player* player, sf::Vector2u screen, ScoreManager* score);
	~PickupManager();

	void Spawn(Level* lvl, Pickup* enemy, sf::Vector2f location);
	void Clear(Level* lvl);

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};

class ScoreManager 
{
	sf::Font font;
	std::unique_ptr<sf::Text> scoreText;
	std::unique_ptr<sf::Text> powerUpCountdownText;

	std::unique_ptr<sf::Sprite> backgroundSprite;
	float gradientRuntime = 0.0f;

public:
	class Round {
	public:
		int fusedCount = 0;
		int enemyIncrement = 0;
		bool isPowerUp = false;
		
		float pwrUpTimer = 0.0f;
		int pwrUpSpawnFusedCount = 0;

		bool win = false;

	public:
		void ActivatePowerUp() {
			pwrUpTimer = 5.0f;
			isPowerUp = true;
		};
		void Update(float deltaTime) {
			if (isPowerUp) {
				pwrUpTimer -= deltaTime;
				if (pwrUpTimer < 0.0f) {
					pwrUpTimer = 0.0f;
					isPowerUp = false;
				}
			}
		};
	};
	
	std::unique_ptr<Round> currentRound;
	int score = 0;

	ScoreManager();
	~ScoreManager();

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	Round* NewRound();

	void AddScore(bool isFused);
	void AddScore(int amount);
};