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
	enum State {
		HOME,
		GAMEPLAY,
		SCORE,
		WAITING_FOR_LEVEL_START,
		WAITING_FOR_NEXT_LEVEL
	} state;

	sf::Vector2u screen;

	Player* player;

	int levelCount = 0;
	std::vector<std::string> levelLib = {
		"../Data/Levels/level.json",
		"../Data/Levels/level2.json",
	};

	Level* lvl;

	std::unique_ptr<ScoreManager> scoreManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<PickupManager> pickupManager;

	float runtime = 0.0f;
	int spawnIncrement = 0;

	bool loadSceneBuffer = false;

	std::unique_ptr<sf::Sprite> logo;
	std::vector<std::unique_ptr<sf::Sprite>> start;
	std::unique_ptr<sf::Sprite> gameOver;

	sf::Font font;
	std::unique_ptr<sf::Text> text;
	std::unique_ptr<sf::Text> scoreText;

	float gradientRuntime = 0.0f;
	std::unique_ptr<sf::Sprite> backgroundSprite;

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

	Level* currentLevel;
	std::vector<Enemy*> enemies;
	int enemySpawnCount;
	float runtime;

public:
	enum State {
		NONE,
		POWERUP
	} state;

	float spawnRate = 4.0f;

	EntityManager(Player* player, sf::Vector2u screen, ScoreManager* score);
	~EntityManager();

	void AssignLevel(Level* lvl);
	void Spawn(Enemy* enemy, sf::Vector2f location);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Clear();
};

class PickupManager 
{
	sf::Vector2u screen;
	Player* player;
	ScoreManager* score;

	Level* currentLevel;

public:
	int bombCount = 0;

	std::vector<Pickup*> pickups;

	PickupManager(Player* player, sf::Vector2u screen, ScoreManager* score);
	~PickupManager();

	void AssignLevel(Level* lvl);
	void Spawn(Pickup* enemy, sf::Vector2f location);
	void Clear();


	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};

class ScoreManager 
{
	Player* player;

	sf::Font font;
	std::unique_ptr<sf::Text> scoreText;
	std::unique_ptr<sf::Text> powerUpCountdownText;

	std::unique_ptr<sf::Sprite> backgroundSprite;
	float gradientRuntime = 0.0f;

	std::vector<std::unique_ptr<sf::Sprite>> livesDisplay;

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
	int lives = 3;

	ScoreManager(Player* player);
	~ScoreManager();

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	Round* NewRound();

	bool Death();

	void Reset();

	void AddScore(bool isFused);
	void AddScore(int amount);
};