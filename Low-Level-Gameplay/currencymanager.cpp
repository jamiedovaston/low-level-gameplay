#include "game.h"

CurrencyManager::CurrencyManager(Player* player, sf::Vector2u screen)
{
	this->player = player;
	this->screen = screen;
}

CurrencyManager::~CurrencyManager()
{
	for (auto& [lvl, pickups] : parent) {
		for (Pickup* p : pickups) {
			delete p;
		}
	}
}

void CurrencyManager::Spawn(Level* lvl, Pickup* pickup, sf::Vector2f location)
{
	if (parent[lvl].empty()) parent[lvl] = std::vector<Pickup*>();

	parent[lvl].push_back(pickup);

	pickup->position = lvl->originPoint + location;
}

void CurrencyManager::Update(float deltaTime)
{
	for (auto& [lvl, pickups] : parent) {
		if(!pickups.empty()) pickups[0]->state = Pickup::State::FUSED;
		for (int i = 0; i < pickups.size(); i++) {
			pickups[i]->Update(deltaTime);

			Pickup* p = pickups[i];
			if (p->state == Pickup::State::PICKED_UP) {
				if (Bomb* b = dynamic_cast<Bomb*>(p))
				{
					// SCORE
				}
				delete p;
				pickups.erase(pickups.begin() + i);
			}
		}
	}
}

void CurrencyManager::Render(sf::RenderWindow* window)
{
	for (auto& [lvl, pickup] : parent) {
		for (Pickup* e : pickup) {
			e->Render(window);
		}
	}
}
