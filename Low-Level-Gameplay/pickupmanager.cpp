#include "game.h"

PickupManager::PickupManager(Player* player, sf::Vector2u screen, ScoreManager* score)
{
	this->player = player;
	this->screen = screen;
	this->score = score;
}

PickupManager::~PickupManager()
{
	for (auto& [lvl, pickups] : parent) {
		for (Pickup* p : pickups) {
			delete p;
		}
	}
}

void PickupManager::Spawn(Level* lvl, Pickup* pickup, sf::Vector2f location)
{
	if (parent[lvl].empty()) parent[lvl] = std::vector<Pickup*>();

	parent[lvl].push_back(pickup);

	pickup->position = lvl->originPoint + location;
}

void PickupManager::Update(float deltaTime)
{
	for (auto& [lvl, pickups] : parent) {
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
				}
				if (PowerUpCoin* puc = dynamic_cast<PowerUpCoin*>(p)) 
				{
					score->currentRound.get()->ActivatePowerUp();
				}
				delete p;
				pickups.erase(pickups.begin() + i);
			}
		}
		for (int i = 0; i < lvl->collisions.size(); i++) {
			for (Pickup* p : pickups) {
				lvl->collisions[i]->Collision(p);
			}
		}
	}
}

void PickupManager::Render(sf::RenderWindow* window)
{
	for (auto& [lvl, pickup] : parent) {
		for (Pickup* e : pickup) {
			e->Render(window);
		}
	}
}
