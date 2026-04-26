#include "game.h"

EntityManager::EntityManager(Player* player, sf::Vector2u screen, ScoreManager* score)
{
	this->screen = screen;
	this->player = player;
	this->score = score;
}

EntityManager::~EntityManager()
{
	for (auto& [lvl, enemies] : parent) {
		for (Enemy* e : enemies) {
			delete e;
		}
	}
}

void EntityManager::AssignLevel(Level* lvl)
{
	parent[lvl] = std::vector<Enemy*>();
}

void EntityManager::Spawn(Level* lvl, Enemy* enemy, sf::Vector2f location)
{
	if (parent[lvl].empty()) parent[lvl] = std::vector<Enemy*>();

	parent[lvl].push_back(enemy);

	enemy->position = lvl->originPoint + location;
}

void EntityManager::Update(float deltaTime)
{
	if (!player->isDead && !score->currentRound.get()->isPowerUp) {
		runtime -= deltaTime;

	}

	for (auto& [lvl, enemies] : parent) {
		if (runtime <= 0.0f) {
			runtime = 5.0f;
			if (enemies.size() < lvl->enemyList.size())
			{
				SpawnPoint* furthest = nullptr;
				float maxDist = -1.0f;

				// GET THE FURTHEST AWAY
				for (auto& colPtr : lvl->collisions) {
					Collider* col = colPtr.get();

					if (auto sp = dynamic_cast<SpawnPoint*>(col)) {
						float d = sp->Distance(player);

						if (d > maxDist) {
							maxDist = d;
							furthest = sp;
						}
					}
				}

				if (furthest) {
					Spawn(lvl, new Skeleton(player, screen), furthest->Position());
				}
			}
		}

		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->Update(deltaTime);

			Enemy* e = enemies[i];
			if (e->flags == Enemy::Enemy_Flags::TRANSFORM) {
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

void EntityManager::ChangeState(State state)
{

}
