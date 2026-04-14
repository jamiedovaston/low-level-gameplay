#pragma once
#include "../Library/json.hpp"
#include <iostream>
#include <fstream>

#include "collisions.h"
#include "entity.h"


class Level 
{
	std::unique_ptr<sf::Texture> background;
	std::unique_ptr<sf::Sprite> backgroundSprite;

public:
	std::vector<std::unique_ptr<Collider>> collisions;

	sf::Vector2f originPoint;

	Level(std::string levelPath);

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};