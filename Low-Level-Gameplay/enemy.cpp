#include "entity.h"

Enemy::Enemy(Player* player, sf::Vector2u screen) : Entity(screen)
{
	this->player = player;
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
    if (player == nullptr) return;


    if (position.x + spriteRect.size.x > player->position.x - player->spriteRect.size.x &&
        position.x - spriteRect.size.x < player->position.x + player->spriteRect.size.x &&
        position.y + spriteRect.size.y > player->position.y - player->spriteRect.size.y &&
        position.y - spriteRect.size.y < player->position.y + player->spriteRect.size.y)
    {
		player->Hit();
    }
}

void Enemy::Render(sf::RenderWindow* window)
{
	if (sprite != nullptr) { window->draw(*sprite); }
}

void Enemy::Hit()
{
}
