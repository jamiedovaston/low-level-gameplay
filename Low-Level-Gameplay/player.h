#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "behaviour.h"

class Player : public Behaviour
{
	// INPUT PRESSED DOWN
	std::map<sf::Keyboard::Key, bool> is_pressed;

	float jumpSpeed = 1000.0f, horizontalSpeed = 1.4f;
	float maxVerticalSpeed = 500.0f, maxHorizontalSpeed = 400.0f;
	float gravity = -.15f;
	float drag = .995f;

	// ANIMATIONS
	float inpDirectionX = 0.0f;
	float previousDirectionX = 0.0f;
	float elapsedTime = 0.0f;
	int frame = 1;

public:
	bool freeze = false;

	Player(sf::Vector2u screen);
	~Player();

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;

	void Animations(float deltaTime);
};