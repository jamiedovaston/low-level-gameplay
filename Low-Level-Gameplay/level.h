#pragma once
#include "../Library/json.hpp"
#include <iostream>
#include <fstream>

#include "collisions.h"
#include "entity.h"

class Level 
{
	std::vector<Entity*> entities;

	sf::Vector2f originPoint;
	
	sf::Texture* background;
	sf::Sprite* backgroundSprite;

	std::vector<Collider*> collisions;
public:
	Level(std::vector<Entity*> entities, std::string levelPath);
	~Level();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};