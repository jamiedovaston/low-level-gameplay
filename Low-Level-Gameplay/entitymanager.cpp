#include "game.h"

EntityManager::EntityManager(Player* player, sf::Vector2u screen)
{
	this->screen = screen;
	this->player = player;
}

EntityManager::~EntityManager()
{
	for (auto& [lvl, enemies] : parent) {
		for (Enemy* e : enemies) {
			delete e;
		}
	}
}

void EntityManager::Spawn(Level* lvl, Enemy* enemy, sf::Vector2f location)
{
	if (parent[lvl].empty()) parent[lvl] = std::vector<Enemy*>();

	parent[lvl].push_back(enemy);

	enemy->position = lvl->originPoint + location;
}

void EntityManager::Update(float deltaTime)
{
	for (auto& [lvl, enemies] : parent) {
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->Update(deltaTime);

			Enemy* e = enemies[i];
			if (e->flags == Enemy::Enemy_Flags::TRANSFORM || e->flags == Enemy::Enemy_Flags::KILL) {
				if (dynamic_cast<Skeleton*>(e))
				{
					if (lvl->enemyList[enemySpawnCount[lvl]] == "Orb") {
						EntityManager::Spawn(lvl, new Orb(player, screen), e->position - lvl->originPoint);
					}
					else if (lvl->enemyList[enemySpawnCount[lvl]] == "Club") {
						EntityManager::Spawn(lvl, new Club(player, screen), e->position - lvl->originPoint);
					}
					else if (lvl->enemyList[enemySpawnCount[lvl]] == "Sphere") {
						EntityManager::Spawn(lvl, new Sphere(player, screen), e->position - lvl->originPoint);
					}
					else std::cout << "# Invalid spawn type! : " << lvl->enemyList[enemySpawnCount[lvl]] << std::endl;

					if (enemySpawnCount[lvl] >= lvl->enemyList.size() - 1) enemySpawnCount[lvl] = 0;
					else enemySpawnCount[lvl]++;

					std::cout << "Enemy Count : " << enemySpawnCount[lvl] << std::endl;
				}
				delete e;
				enemies.erase(enemies.begin() + i);
			}
		}
		// ENEMY COLLISIONS
		for (int i = 0; i < lvl->collisions.size(); i++) {
			for (Enemy* e : enemies) {
				lvl->collisions[i]->Collision(e);
			}
		}
	}
}

void EntityManager::Render(sf::RenderWindow* window)
{
	for (auto& [lvl, enemies] : parent) {
		for (Enemy* e : enemies) {
			e->Render(window);
		}
	}
}

void EntityManager::Clear(Level* lvl)
{
	for (Enemy* e : parent[lvl]) {
		delete e;
	}
	parent[lvl].clear();
}
