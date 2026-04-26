#include "enemy.h"

Enemy::Enemy(Player* player, sf::Vector2u screen) : Entity(screen)
{
	this->player = player;

    coinSize = sf::Vector2i(36, 36);
    coin = new sf::Sprite(*LoadResource("../Images/coins.png"));
    coin->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), coinSize));
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
    runtime += deltaTime;

    coin->setPosition(sf::Vector2f(position.x - spriteRect.position.x - spriteRect.size.x, position.y - spriteRect.position.y - spriteRect.size.y));

    if (player == nullptr) return;

    // WAIT FOR A SECOND
    if (runtime <= 1.0f) return;

    // MULTIPLIED FOR AFFORDANCE
    if (position.x + (spriteRect.size.x * .8f) > player->position.x - player->spriteRect.size.x &&
        position.x - (spriteRect.size.x * .8f) < player->position.x + player->spriteRect.size.x &&
        position.y + (spriteRect.size.y * .8f) > player->position.y - player->spriteRect.size.y &&
        position.y - (spriteRect.size.y * .8f) < player->position.y + player->spriteRect.size.y)
    {
        if (flags == Enemy_Flags::POWERUP) {
            flags = Enemy_Flags::KILL;
        }
        else player->Hit();
    }
}

void Enemy::Render(sf::RenderWindow* window)
{
    if (flags == Enemy_Flags::POWERUP) { window->draw(*coin); }
    else if (sprite != nullptr) { window->draw(*sprite); }
}