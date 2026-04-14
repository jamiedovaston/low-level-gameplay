#include "entity.h"

Entity::Entity(sf::Vector2u screen)
{
    sprite = nullptr;
}

Entity::~Entity()
{
    delete sprite;
    sprite = nullptr;
}
