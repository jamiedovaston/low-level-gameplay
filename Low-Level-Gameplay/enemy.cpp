#include "entity.h"

Enemy::Enemy(sf::Vector2u screen) : Entity(screen)
{

}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
		
}

void Enemy::Render(sf::RenderWindow* window)
{
	if (sprite != nullptr) { window->draw(*sprite); }
}
