#include "collisions.h"

Block::Block(sf::Vector2f originPoint, float x, float y, float w, float h) : Collider(originPoint)
{
    this->originPoint = originPoint;
    this->x = originPoint.x + x;
    this->y = originPoint.y + y;
    this->w = w;
    this->h = h;

    block = new sf::Texture("../Images/block.png");
    sprite = new sf::Sprite(*block);

    sprite->setScale(sf::Vector2f(w / 23.0f, h / 23.0f));
    sprite->setPosition(sf::Vector2f(this->x, this->y));
}

Block::~Block()
{
    delete block;
    block = nullptr;

    delete sprite;
    sprite = nullptr;
}

bool Block::Collision(Entity* behaviour)
{
    bool isGrounded = false;
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

        // Same idea as ScreenBounds
        if (playerBottom > y - groundCheck &&
            playerBottom < y + groundCheck &&
            behaviour->position.x + behaviour->spriteRect.size.x > x &&
            behaviour->position.x - behaviour->spriteRect.size.x < x + w)
        {
            isGrounded = true;
        }

        if (minX < minY)
        {
            if (left < right)
                behaviour->position.x = x - behaviour->spriteRect.size.x;
            else
                behaviour->position.x = x + w + behaviour->spriteRect.size.x;

            behaviour->projectedVelocity.x = 0.0f;
            behaviour->velocity.x = 0.0f;
        }
        else
        {
            if (top < bottom) {
                behaviour->position.y = y - behaviour->spriteRect.size.y;
            }
            else {
                behaviour->position.y = y + h + behaviour->spriteRect.size.y;
            }

            behaviour->projectedVelocity.y = 0.0f;
            behaviour->velocity.y = 0.0f;
        }
    }

    return isGrounded;
}

void Block::Render(sf::RenderWindow* window)
{
    if (sprite != nullptr) { window->draw(*sprite); }
}
