#include "collisions.h"

ScreenBounds::ScreenBounds(sf::Vector2u screen) : Collider(screen)
{
    border = new sf::Texture("../Images/Border.png");
    sprite = new sf::Sprite(*border);
}

ScreenBounds::~ScreenBounds()
{
    delete border;
    border = nullptr;

    delete sprite;
    sprite = nullptr;
}

bool ScreenBounds::Collision(Behaviour* behaviour)
{
    bool isGrounded = false;
    if (behaviour->position.x + behaviour->radius > screenSize.x - borderSize) {
        behaviour->position.x = screenSize.x - behaviour->radius - borderSize;

        behaviour->projectedVelocity.x = 0.0f;
        behaviour->velocity.x = 0.0f;
    }
    if (behaviour->position.x - behaviour->radius < 0.0f + borderSize) {
        behaviour->position.x = 0.0f + behaviour->radius + borderSize;

        behaviour->projectedVelocity.x = 0.0f;
        behaviour->velocity.x = 0.0f;
    }

    if (behaviour->position.y + behaviour->radius > screenSize.y - borderSize - 10.0f) {
        isGrounded = true;
    }

    if (behaviour->position.y + behaviour->radius > screenSize.y - borderSize) {
        behaviour->position.y = screenSize.y - behaviour->radius - borderSize;
        behaviour->velocity.y = 0.0f;
        behaviour->projectedVelocity.y = 0.0f;
    }
    if (behaviour->position.y - behaviour->radius < 0.0f + borderSize) {
        behaviour->position.y = 0.0f + behaviour->radius + borderSize;
        behaviour->velocity.y = 0.0f;
        behaviour->projectedVelocity.y = 0.0f;
    }
    return isGrounded;
}

void ScreenBounds::Render(sf::RenderWindow* window)
{
    if (sprite != nullptr) { window->draw(*sprite); }
}