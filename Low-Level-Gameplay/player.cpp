#include "entity.h"

Player::Player(sf::Vector2u screen) : Entity(screen)
{
    // CREATE PLAYER
    spriteSize = sf::Vector2i(65, 68);
    texture = new sf::Texture("../Images/jack-sprite-sheet.png");
    sprite = new sf::Sprite(*texture);
    sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), spriteSize));
    spriteRect = sf::FloatRect(sf::Vector2f(28.0f / 2.0f, 25.0f), sf::Vector2f(37.0f / 2.0f, 43.0f / 2.0f));

    // SPAWN AT POSITION
    position = sf::Vector2f(screen.x / 2.0f, screen.y / 2.0f);
}

Player::~Player()
{

}

void Player::Update(float deltaTime) 
{
    // INPUT DIRECTION
    sf::Vector2f direction(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !is_pressed[sf::Keyboard::Key::Space])
    {
        is_pressed[sf::Keyboard::Key::Space] = true;
        if (isGrounded) {
            projectedVelocity.y = jumpSpeed;
        }
        else {
            projectedVelocity.y = 0.0f;
        }
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && is_pressed[sf::Keyboard::Key::Space])
        is_pressed[sf::Keyboard::Key::Space] = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        direction.y += 1.0f;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        direction.x -= 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        direction.y -= 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        direction.x += 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && !is_pressed[sf::Keyboard::Key::LShift])
    {
        is_pressed[sf::Keyboard::Key::LShift] = true;
        freeze = !freeze;
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && is_pressed[sf::Keyboard::Key::LShift])
        is_pressed[sf::Keyboard::Key::LShift] = false;

    if (freeze) return;

    // ANIMATIONS
    inpDirectionX = direction.x;
    Animations(deltaTime);

    // GROUNDED BUFFER
    groundedBuffer -= deltaTime;
    isGrounded = groundedBuffer > 0.0f;

    // X
    // INPUT * SPEED
    float projectedVelocityX = direction.x * horizontalSpeed;
    if(velocity.x + projectedVelocityX < maxHorizontalSpeed && velocity.x + projectedVelocityX > -maxHorizontalSpeed)
        velocity.x += projectedVelocityX;

    // Y
    float projectedVelocityY = gravity * (projectedVelocity.y < 0.0f ? (direction.y < 0.0f ? 2.0f : 1.0f) : (direction.y > 0.0f ? .5f : direction.y < 0.0f ? 2.0f : 1.0f));

    projectedVelocity.y += projectedVelocityY;
    velocity.y = std::clamp(projectedVelocity.y, -maxVerticalSpeed, maxVerticalSpeed);

    // DRAG
    velocity.x *= drag;

    // INVERT VELOCITY Y (defaults to downwards being positive) AND ADDS TO POSITION
    position += sf::Vector2f(velocity.x, -velocity.y) * deltaTime;

    sprite->setPosition(sf::Vector2f(position.x - spriteRect.position.x - spriteRect.size.x, position.y - spriteRect.position.y - spriteRect.size.y));
}

void Player::Render(sf::RenderWindow* window) 
{
    if (sprite != nullptr) { window->draw(*sprite); }
}

void Player::Animations(float deltaTime)
{
    elapsedTime += deltaTime;

    // DIRECTION X
    if (previousDirectionX != inpDirectionX) {
        elapsedTime = 0.0f;
        frame = 0;
        previousDirectionX = inpDirectionX;
    }
    else if (isGrounded) // GROUNDED
    {
        if (inpDirectionX > 0.0f) // RIGHT
        {
            if (elapsedTime > .075f) {
                elapsedTime = 0.0f;
                frame++;
                if (frame > 3) { frame = 0; }
            }
            sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * frame, spriteSize.y), spriteSize));
        }
        else if (inpDirectionX < 0.0f) // LEFT
        {
            if (elapsedTime > .075f) {
                elapsedTime = 0.0f;
                frame++;
                if (frame > 3) { frame = 0; }
            }
            sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * frame, spriteSize.y * 2), spriteSize));
        }
        else // STRAIGHT
        {
            sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), spriteSize));
        }
    }
    else // AIRBORNE
    {
        if (velocity.y > 0.0f) {
            sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, spriteSize.y * 3), spriteSize));
        }
        else {
            if (inpDirectionX > 0.0f) // RIGHT
                sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * 2, spriteSize.y * 3), spriteSize));
            else if (inpDirectionX < 0.0f) // LEFT
                sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * 3, spriteSize.y * 3), spriteSize));
            else // STRAIGHT
                sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x, spriteSize.y * 3), spriteSize));
        }
    }
}
