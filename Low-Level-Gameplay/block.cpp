#include "collisions.h"

Block::Block(sf::Vector2u screen, float x, float y, float w, float h) : Collider(screen)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    box = sf::RectangleShape(sf::Vector2f(w, h));
    box.setPosition(sf::Vector2f(x, y));
    box.setFillColor(sf::Color::Red);
}

bool Block::Collision(Behaviour* behaviour)
{
    if (behaviour->position.x + behaviour->radius > x && behaviour->position.x - behaviour->radius < x + w &&
        behaviour->position.y + behaviour->radius > y && behaviour->position.y - behaviour->radius < y + h)
    {
        float left = (behaviour->position.x + behaviour->radius) - x;
        float right = (x + w) - (behaviour->position.x - behaviour->radius);
        float top = (behaviour->position.y + behaviour->radius) - y;
        float bottom = (y + h) - (behaviour->position.y - behaviour->radius);

        float minX = (left < right) ? left : right;
        float minY = (top < bottom) ? top : bottom;

        if (minX < minY)
        {
            if (left < right)
                behaviour->position.x = x - behaviour->radius;
            else
                behaviour->position.x = x + w + behaviour->radius;

            behaviour->projectedVelocity.x = 0.0f;
            behaviour->velocity.x = 0.0f;
        }
        else
        {
            if (top < bottom)
                behaviour->position.y = y - behaviour->radius;
            else
                behaviour->position.y = y + h + behaviour->radius;

            behaviour->projectedVelocity.y = 0.0f;
            behaviour->velocity.y = 0.0f;
        }

        return true;
    }

    return false;
}

void Block::Render(sf::RenderWindow* window)
{
    window->draw(box);
}
