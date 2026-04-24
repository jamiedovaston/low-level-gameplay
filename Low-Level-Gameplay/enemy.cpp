#include "enemy.h"

Enemy::Enemy(Player* player, sf::Vector2u screen) : Entity(screen)
{
	this->player = player;
    coin = new sf::Sprite(*LoadResource("../Images/coins.png").get());
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
    runtime += deltaTime;

    if (player == nullptr) return;

    // WAIT FOR A SECOND
    if (runtime <= 1.0f) return;

    // MULTIPLIED FOR AFFORDANCE
    if (position.x + (spriteRect.size.x * .8f) > player->position.x - player->spriteRect.size.x &&
        position.x - (spriteRect.size.x * .8f) < player->position.x + player->spriteRect.size.x &&
        position.y + (spriteRect.size.y * .8f) > player->position.y - player->spriteRect.size.y &&
        position.y - (spriteRect.size.y * .8f) < player->position.y + player->spriteRect.size.y)
    {
		player->Hit();
    }
}

void Enemy::Render(sf::RenderWindow* window)
{
	if (sprite != nullptr) { window->draw(*sprite); }
}