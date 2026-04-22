#pragma once
#include "entity.h"

class Pickup : public Entity 
{
protected:
	Player* player;

	// ANIMATIONS
	float elapsedTime = 0.0f;
	int frame = 1;
public:
	enum State {
		NONE,
		FUSED,
		PICKED_UP
	} state = State::NONE;

	Pickup(Player* player, sf::Vector2u screen);
	~Pickup();

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;

	virtual void OnPickup() = 0;
	virtual void Animations(float deltaTime) = 0;
};

class Bomb : public Pickup 
{
public:
	Bomb(Player* player, sf::Vector2u screen);
	~Bomb();
	
	void OnPickup() override;
	void Animations(float deltaTime) override;
};
