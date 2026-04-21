#include "collisions.h"

SpawnPoint::SpawnPoint(sf::Vector2f originPoint, float x, float y) : Block(originPoint, x, y, 0.0f, 0.0f)
{
	
}

SpawnPoint::~SpawnPoint()
{

}

void SpawnPoint::Collision(Entity* behaviour)
{

}

void SpawnPoint::Render(sf::RenderWindow* window)
{

}

// SQUARED FOR SPEED
float SpawnPoint::Distance(Player* player)
{
    float dx = player->position.x - x;
    float dy = player->position.y - y;
    return dx * dx + dy * dy;
}

sf::Vector2f SpawnPoint::Position()
{
	return sf::Vector2f(x, y);
}
