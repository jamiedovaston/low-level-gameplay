#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "level.h"
#include "collisions.h"
#include "entity.h"

class Game 
{
	sf::Vector2u screen;

	Player* player;
	Level* lvl;

	std::vector<Enemy*> enemies;

	sf::Font font;
	sf::Text* text;

	float runtime = 0.0f;
public:
	Game(sf::Vector2u screenSize);
	~Game();

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};