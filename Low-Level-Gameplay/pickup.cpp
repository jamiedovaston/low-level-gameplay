#include "pickup.h"

Pickup::Pickup(Player* player, sf::Vector2u screen) : Entity(screen)
{
    state = State::NONE;

    this->player = player;
}

Pickup::~Pickup()
{

}

void Pickup::Update(float deltaTime)
{
    if (player == nullptr) return;
    if (player->freeze.size() != 0) return;

    Animations(deltaTime);

    if (position.x + spriteRect.size.x > player->position.x - player->spriteRect.size.x &&
        position.x - spriteRect.size.x < player->position.x + player->spriteRect.size.x &&
        position.y + spriteRect.size.y > player->position.y - player->spriteRect.size.y &&
        position.y - spriteRect.size.y < player->position.y + player->spriteRect.size.y)
    {
        if (state != State::PICKED_UP) {
            OnPickup(); 
            state = State::PICKED_UP;
        }
    }

    sprite->setPosition(sf::Vector2f(position.x - spriteRect.position.x - spriteRect.size.x, position.y - spriteRect.position.y - spriteRect.size.y));
}

void Pickup::Render(sf::RenderWindow* window)
{
    if (sprite != nullptr) { window->draw(*sprite); }
}
