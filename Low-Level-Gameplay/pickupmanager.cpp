#include "game.h"

PickupManager::PickupManager(Player* player, sf::Vector2u screen, ScoreManager* score)
{
	this->player = player;
	this->screen = screen;
	this->score = score;
}

PickupManager::~PickupManager()
{
	for (Pickup* p : pickups) {
		delete p;
	}
}

void PickupManager::AssignLevel(Level* lvl)
{
	currentLevel = lvl;
	pickups = std::vector<Pickup*>();
}

void PickupManager::Spawn(Pickup* pickup, sf::Vector2f location)
{
	if (pickups.empty()) pickups = std::vector<Pickup*>();

	if (dynamic_cast<Bomb*>(pickup)) { bombCount++; }

	pickups.push_back(pickup);

	pickup->position = currentLevel->originPoint + location;
}

void PickupManager::Clear()
{
	for (Pickup* a : pickups) {
		delete a;
		a = nullptr;
	}
	pickups.clear();

	bombCount = 0;
}

void PickupManager::Update(float deltaTime)
{
	Bomb* firstBomb = nullptr;

	for (Pickup* p : pickups) {
		if (p->state != Pickup::State::PICKED_UP) {
			if (Bomb* b = dynamic_cast<Bomb*>(p)) {
				firstBomb = b;
				break;
			}
		}
	}

	if (firstBomb) {
		firstBomb->bstate = Bomb::BState::FUSED;
	}

	for (int i = 0; i < pickups.size(); i++) {
		Pickup* p = pickups[i];
		p->Update(deltaTime);

		if (p->state == Pickup::State::PICKED_UP) {
			if (Bomb* b = dynamic_cast<Bomb*>(p))
			{
				score->AddScore((b->bstate == Bomb::BState::FUSED));
				if (b->bstate == Bomb::BState::FUSED) score->currentRound->pwrUpSpawnFusedCount++;
				if (score->currentRound->pwrUpSpawnFusedCount >= 10) // FUSED POWER UP COUNT
				{
					score->currentRound->pwrUpSpawnFusedCount = 0;

					std::vector<SpawnPoint*> spawnPoints;

					for (Collider* colPtr : currentLevel->collisions)
					{
						Collider* col = colPtr;

						if (auto sp = dynamic_cast<SpawnPoint*>(col)) {
							spawnPoints.push_back(sp);
						}
					}
					
					int random = rand() % spawnPoints.size();
					Spawn(new PowerUpCoin(player, screen), spawnPoints[random]->Position());
				}

				bombCount--;
			}
			if (PowerUpCoin* puc = dynamic_cast<PowerUpCoin*>(p)) 
			{
				score->currentRound->ActivatePowerUp();
			}
			delete p;
			pickups.erase(pickups.begin() + i);
		}
	}
	for (int i = 0; i < currentLevel->collisions.size(); i++) {
		for (Pickup* p : pickups) {
			currentLevel->collisions[i]->Collision(p);
		}
	}
}

void PickupManager::Render(sf::RenderWindow* window) const
{
	for (Pickup* p : pickups) {
		if(p != nullptr)
			p->Render(window);
	}
}
