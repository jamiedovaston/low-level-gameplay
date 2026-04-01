#pragma onces
#include "collisions.h"
#include "../Library/json.hpp"
#include <iostream>
#include <fstream>
#include <string>

class Level 
{
	Player* player;

	sf::Vector2f originPoint;
	
	sf::Texture* background;
	sf::Sprite* backgroundSprite;

	std::vector<Collider*> collisions;
public:
	Level(Player* player, std::string levelPath);
	~Level();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};