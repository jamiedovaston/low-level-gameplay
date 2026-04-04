#include "game.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
	for (auto& [lvl, enemies] : parent) {
		for (Enemy* e : enemies) {
			delete e;
		}
	}
}

int EntityManager::Spawn(Level* lvl, Enemy* enemy, sf::Vector2f location)
{
	if (parent[lvl].empty()) {
		parent[lvl] = std::vector<Enemy*>();
	}

	parent[lvl].push_back(enemy);
	sf::Vector2f spawnPoint = lvl->originPoint + location;

	enemy->position = spawnPoint;

	return 0;
}

void EntityManager::Update(float deltaTime)
{
	for (auto& [lvl, enemies] : parent) {
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->Update(deltaTime);

			enemies.erase(
				std::remove_if(enemies.begin(), enemies.end(),
					[](Enemy* ptr) {
						if (ptr->flags == (Enemy::Enemy_Flags::TRANSFORM || Enemy::Enemy_Flags::KILL)) {
							delete ptr;
							return true;
						}
						return false;
					}),
				enemies.end()
			);
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
