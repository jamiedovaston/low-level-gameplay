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

public:
	bool freeze = false;

	Player(sf::Vector2u screen);
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
};