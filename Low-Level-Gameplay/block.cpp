#include "collisions.h"

Block::Block(sf::Vector2f originPoint, float x, float y, float w, float h) : Collider(originPoint)
{
    this->originPoint = originPoint;
    this->x = originPoint.x + x;
    this->y = originPoint.y + y;
    this->w = w;
    this->h = h;

    sprite = new sf::Sprite(*LoadResource("../Images/block.png"));

    sprite->setScale(sf::Vector2f(w / 23.0f, h / 23.0f));
    sprite->setPosition(sf::Vector2f(this->x, this->y));
}

Block::~Block()
{
    delete sprite;
    sprite = nullptr;
}

void Block::Collision(Entity* behaviour)
{
    if (behaviour->position.x + behaviour->spriteRect.size.x > x && behaviour->position.x - behaviour->spriteRect.size.x < x + w &&
        behaviour->position.y + behaviour->spriteRect.size.y > y && behaviour->position.y - behaviour->spriteRect.size.y < y + h)
    {
        float left = (behaviour->position.x + behaviour->spriteRect.size.x) - x;
        float right = (x + w) - (behaviour->position.x - behaviour->spriteRect.size.x);
        float top = (behaviour->position.y + behaviour->spriteRect.size.y) - y;
        float bottom = (y + h) - (behaviour->position.y - behaviour->spriteRect.size.y);

        float minX = (left < right) ? left : right;
        float minY = (top < bottom) ? top : bottom;

        const float groundCheck = 10.0f;

        float playerBottom = behaviour->position.y + behaviour->spriteRect.size.y;

        // AI BEHAVIOUR
        if (Skeleton* e = dynamic_cast<Skeleton*>(behaviour))
        {
            if (e->position.x + behaviour->spriteRect.size.x > (x + w)) { // RIGHT
                e->ChangeDirection(sf::Vector2f(-1.0f, 0.0f));
            }
            if (e->position.x - behaviour->spriteRect.size.x < (x)) { // LEFT
                e->ChangeDirection(sf::Vector2f(1.0f, 0.0f));
            }
        }
        else if (Club* e = dynamic_cast<Club*>(behaviour))
        {
            if (minX < minY)
            {
                e->velocity.x *= -5.0f;
                e->projectedVelocity.x = e->velocity.x;
            }
            else
            {
                e->velocity.y *= -5.0f;
                e->projectedVelocity.y = e->velocity.y;
            }
        }
        else if (Sphere* e = dynamic_cast<Sphere*>(behaviour))
        {
            if (minX < minY)
            {
                e->velocity.x *= -5.0f;
                e->projectedVelocity.x = e->velocity.x;
            }
            else
            {
                e->velocity.y *= -5.0f;
                e->projectedVelocity.y = e->velocity.y;

                e->direction.y = -e->direction.y;
            }
        }
        else if (Orb* e = dynamic_cast<Orb*>(behaviour))
        {
            if (minX < minY)
            {
                e->velocity.x *= -5.0f;
                e->projectedVelocity.x = e->velocity.x;

                e->direction.x = -e->direction.x;
            }
            else
            {
                e->velocity.y *= -5.0f;
                e->projectedVelocity.y = e->velocity.y;
            }
        }

        // ====

        // Same idea as ScreenBounds
        if (playerBottom > y - groundCheck &&
            playerBottom < y + groundCheck &&
            behaviour->position.x + behaviour->spriteRect.size.x > x &&
            behaviour->position.x - behaviour->spriteRect.size.x < x + w)
        {
            behaviour->groundedBuffer = 0.01f;
        }

        bool isBall = dynamic_cast<Club*>(behaviour) != nullptr;

        if (minX < minY)
        {
            if (left < right)
                behaviour->position.x = x - behaviour->spriteRect.size.x;
            else
                behaviour->position.x = x + w + behaviour->spriteRect.size.x;

            if (!isBall)
            {
                behaviour->projectedVelocity.x = 0.0f;
                behaviour->velocity.x = 0.0f;
            }
        }
        else
        {
            if (top < bottom)
                behaviour->position.y = y - behaviour->spriteRect.size.y;
            else
                behaviour->position.y = y + h + behaviour->spriteRect.size.y;

            if (!isBall)
            {
                behaviour->projectedVelocity.y = 0.0f;
                behaviour->velocity.y = 0.0f;
            }
        }
    }
}

void Block::Render(sf::RenderWindow* window)
{
    if (sprite != nullptr) { window->draw(*sprite); }
}
