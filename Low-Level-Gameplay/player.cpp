#include "player.h"
#include <iostream>
#include <cmath>

Behaviour::Behaviour(sf::Vector2u screen)
{
    screenSize = screen;
}

Player::Player(sf::Vector2u screen) : Behaviour(screen)
{
    // CREATE PLAYER
    sprite = sf::CircleShape(radius);
    // SPAWN AT POSITION
    position = sf::Vector2f(screen.x / 2.0f, screen.y / 2.0f);
    // SET COLOUR
    sprite.setFillColor(sf::Color::Green);
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
            if(projectedVelocity.y < 0.0f)
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

    sprite.setPosition(sf::Vector2f(position.x - radius, position.y - radius));
}

void Player::Render(sf::RenderWindow* window) 
{
    window->draw(sprite);
}
