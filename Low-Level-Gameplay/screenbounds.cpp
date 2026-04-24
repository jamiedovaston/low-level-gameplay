#include "collisions.h"

ScreenBounds::ScreenBounds(sf::Vector2f originPoint) : Collider(originPoint)
{
    this->originPoint = originPoint;
    sprite = new sf::Sprite(*LoadResource("../Images/Border.png"));
    sprite->setPosition(originPoint);
}

ScreenBounds::~ScreenBounds()
{
    delete sprite;
    sprite = nullptr;
}

void ScreenBounds::Collision(Entity* behaviour)
{
    if (behaviour->position.x + behaviour->spriteRect.size.x > levelSize.x - (borderSize + originPoint.x)) {
        behaviour->position.x = originPoint.x + levelSize.x - behaviour->spriteRect.size.x - borderSize;

        behaviour->projectedVelocity.x = 0.0f;
        behaviour->velocity.x = 0.0f;

        if (Sphere* e = dynamic_cast<Sphere*>(behaviour)) {
            e->projectedDirection = -1.0f;
        }
        if (Orb* e = dynamic_cast<Orb*>(behaviour)) {
            e->direction.x = -1.0f;
        }
        if (PowerUpCoin* p = dynamic_cast<PowerUpCoin*>(behaviour)) {
            p->direction.x = -1.0f;
        }
    }
    if (behaviour->position.x - behaviour->spriteRect.size.x < 0.0f + (borderSize + originPoint.x)) {
        behaviour->position.x = originPoint.x + behaviour->spriteRect.size.x + borderSize;

        behaviour->projectedVelocity.x = 0.0f;
        behaviour->velocity.x = 0.0f;

        if (Sphere* e = dynamic_cast<Sphere*>(behaviour)) {
            e->projectedDirection = 1.0f;
        }
        else if (Orb* e = dynamic_cast<Orb*>(behaviour)) {
            e->direction.x = 1.0f;
        }
        else if (PowerUpCoin* p = dynamic_cast<PowerUpCoin*>(behaviour)) {
            p->direction.x = 1.0f;
        }
    }

    if (behaviour->position.y + behaviour->spriteRect.size.y > originPoint.y + levelSize.y - borderSize) {
        behaviour->position.y = originPoint.y + levelSize.y - behaviour->spriteRect.size.y - borderSize;

        behaviour->groundedBuffer = 0.01f; // GROUNDED
        behaviour->velocity.y = 0.0f;
        behaviour->projectedVelocity.y = 0.0f;

        if (Sphere* e = dynamic_cast<Sphere*>(behaviour)) {
            e->direction.y = -1.0f;
        }
        else if (Orb* e = dynamic_cast<Orb*>(behaviour)) {
            e->projectedDirection = -1.0f;
        }
        else if (PowerUpCoin* p = dynamic_cast<PowerUpCoin*>(behaviour)) {
            p->direction.y = -1.0f;
        }

        if (Enemy* e = dynamic_cast<Skeleton*>(behaviour)) {
            e->flags = Enemy::Enemy_Flags::TRANSFORM;
        }
    }
    if (behaviour->position.y - behaviour->spriteRect.size.y < 0.0f + (borderSize + originPoint.y)) {
        behaviour->position.y = originPoint.y + behaviour->spriteRect.size.y + borderSize;
        behaviour->velocity.y = 0.0f;
        behaviour->projectedVelocity.y = 0.0f;

        if (Sphere* e = dynamic_cast<Sphere*>(behaviour)) {
            e->direction.y = 1.0f;
        }
        else if (Orb* e = dynamic_cast<Orb*>(behaviour)) {
            e->projectedDirection = 1.0f;
        }
        else if (PowerUpCoin* p = dynamic_cast<PowerUpCoin*>(behaviour)) {
            p->direction.y = 1.0f;
        }
    }
}

void ScreenBounds::Render(sf::RenderWindow* window)
{
    if (sprite != nullptr) { window->draw(*sprite); }
}