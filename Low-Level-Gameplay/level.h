#pragma once
#include "../Library/json.hpp"
#include <iostream>
#include <fstream>

#include "collisions.h"
#include "entity.h"


class Level 
{
	sf::Texture* background;
	sf::Sprite* backgroundSprite;

public:
	std::vector<Collider*> collisions;

	sf::Vector2f originPoint;

	Level(std::string levelPath);
	~Level();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};