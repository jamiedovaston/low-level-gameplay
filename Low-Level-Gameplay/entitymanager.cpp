#include "game.h"

EntityManager::EntityManager(Player* player, sf::Vector2u screen, ScoreManager* score)
{
	this->screen = screen;
	this->player = player;
	this->score = score;
}

EntityManager::~EntityManager()
{
	for (Enemy* e : enemies) {
		delete e;
	}
}

void EntityManager::AssignLevel(Level* lvl)
{
	currentLevel = lvl;
	enemies = std::vector<Enemy*>();
	runtime = 0.0f;
	enemySpawnCount = 0.0f;
}

void EntityManager::Spawn(Enemy* enemy, sf::Vector2f location)
{
	if (currentLevel == nullptr) return;

	enemies.push_back(enemy);

	enemy->position = currentLevel->originPoint + location;
}

void EntityManager::Update(float deltaTime)
{
	if (currentLevel == nullptr) return;

	if (!player->freeze.size() > 0 && !score->currentRound->isPowerUp) {
		runtime -= deltaTime;
	}
	if (score->currentRound.get()->isPowerUp) {
		runtime = 0.0f;
	}

	if (runtime < 0.0f) {
		runtime = spawnRate;
		if (enemies.size() < currentLevel->enemyList.size())
		{
			SpawnPoint* furthest = nullptr;
			float maxDist = -1.0f;

			// GET THE FURTHEST AWAY
			for (Collider* col : currentLevel->collisions) {

				if (auto sp = dynamic_cast<SpawnPoint*>(col)) {
					float d = sp->Distance(player);

					if (d > maxDist) {
						maxDist = d;
						furthest = sp;
					}
				}
			}

			if (furthest) {
				Spawn(new Skeleton(player, screen, furthest->isRight), furthest->Position());
			}
		}
	}

	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Update(deltaTime);

		Enemy* e = enemies[i];
		if (e->flags == Enemy::Enemy_Flags::TRANSFORM) {
			if (dynamic_cast<Skeleton*>(e))
			{
				if (currentLevel->enemyList[enemySpawnCount] == "Orb") {
					EntityManager::Spawn(new Orb(player, screen), e->position - currentLevel->originPoint);
				}
				else if (currentLevel->enemyList[enemySpawnCount] == "Club") {
					EntityManager::Spawn(new Club(player, screen), e->position - currentLevel->originPoint);
				}
				else if (currentLevel->enemyList[enemySpawnCount] == "Sphere") {
					EntityManager::Spawn(new Sphere(player, screen), e->position - currentLevel->originPoint);
				}
				else std::cout << "# Invalid spawn type! : " << currentLevel->enemyList[enemySpawnCount] << std::endl;

				if (enemySpawnCount >= currentLevel->enemyList.size() - 1) enemySpawnCount = 0;
				else enemySpawnCount++;
			}
		}
		if (e->flags == Enemy::Enemy_Flags::TRANSFORM || e->flags == Enemy::Enemy_Flags::KILL)
		{
			if(e->flags == Enemy::Enemy_Flags::KILL) score->AddScore(1000);

			delete e;
			enemies.erase(enemies.begin() + i);
			break;
		}

		if (score->currentRound.get()->isPowerUp) {
			e->flags = Enemy::Enemy_Flags::POWERUP;
		}
		else {
			e->flags = Enemy::Enemy_Flags::NONE;
		}
	}
	// ENEMY COLLISIONS
	for (int i = 0; i < currentLevel->collisions.size(); i++) {
		for (Enemy* e : enemies) {
			currentLevel->collisions[i]->Collision(e);
		}
	}
}

void EntityManager::Render(sf::RenderWindow* window)
{
	for (Enemy* e : enemies) {
		if(e != nullptr) e->Render(window);
	}
}

void EntityManager::Clear()
{
	for (Enemy* e : enemies) {
		delete e;
	}
	enemies.clear();
}