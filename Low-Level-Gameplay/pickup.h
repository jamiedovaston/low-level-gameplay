#pragma once
#include "entity.h"

class Pickup : public Entity {
	Pickup(Player* player, sf::Vector2u screen);
	~Pickup();
};

class Bomb : public Pickup {

};
