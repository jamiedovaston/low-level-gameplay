#include "entity.h"

Entity::Entity(sf::Vector2u screen)
{
    sprite = nullptr;
    texture = nullptr;
}

Entity::~Entity()
{
    delete texture;
    texture = nullptr;

    delete sprite;
    sprite = nullptr;
}
