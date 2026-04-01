#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "entity.h"
#include "collisions.h"
#include "level.h"

class Game 
{
	sf::Vector2u screen;

	Player* player;
	Level* level;

	sf::Text* text;
public:
	Game(sf::Vector2u screenSize);
	~Game();

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};