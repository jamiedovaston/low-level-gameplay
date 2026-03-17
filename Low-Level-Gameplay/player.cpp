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
    player = sf::CircleShape(radius);
    // SPAWN AT POSITION
    position = sf::Vector2f(screen.x / 2.0f, screen.y / 2.0f);
    // SET COLOUR
    player.setFillColor(sf::Color::Green);
}

void Player::Start() 
{
    x = (screenSize.x / 2) - (w / 2);
    y = (screenSize.y / 2) - (h / 2);
    box = sf::RectangleShape(sf::Vector2f(w, h));
    box.setPosition(sf::Vector2f(x, y));
    box.setFillColor(sf::Color::Red);
}

void Player::Update(float deltaTime) 
{
    // INPUT DIRECTION
    sf::Vector2f direction(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        projectedVelocity.y = 600.0f;
    }

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !is_pressed[sf::Keyboard::Key::Space])
    {
        is_pressed[sf::Keyboard::Key::Space] = true;
        if(velocity.y < 0.0f)
            velocity.y = 0.0f;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && is_pressed[sf::Keyboard::Key::Space])
        is_pressed[sf::Keyboard::Key::Space] = false;

    if (freeze) return;

    // X
    // INPUT * SPEED
    float projectedVelocityX = direction.x * horizontalSpeed;
    if(velocity.x + projectedVelocityX < maxHorizontalSpeed && velocity.x + projectedVelocityX > -maxHorizontalSpeed)
        velocity.x += projectedVelocityX;

    // Y
    // GRAVITY + (INPUT * SPEED)
    // CLAMP
    // if (velocity.y + projectedVelocityY < maxVerticalSpeed && velocity.y + projectedVelocityY > -maxVerticalSpeed)
    //     velocity.y += projectedVelocityY > maxVerticalSpeed;

    float projectedVelocityY = gravity * (projectedVelocity.y < 0.0f ? (direction.y < 0.0f ? 2.0f : 1.0f) : (direction.y > 0.0f ? .5f : direction.y < 0.0f ? 2.0f : 1.0f));

    projectedVelocity.y += projectedVelocityY;
    velocity.y = std::clamp(projectedVelocity.y, -maxVerticalSpeed, maxVerticalSpeed);

    // DRAG
    velocity.x *= drag;

    std::cout << CollisionBoxTest() << std::endl;

    // INVERT VELOCITY Y (defaults to downwards being positive) AND ADDS TO POSITION
    position += sf::Vector2f(velocity.x, -velocity.y) * deltaTime;

    // KEEP BALL IN SCREEN BOUNDS (0, 0 is top left)
    ScreenBoundsCollision();


    player.setPosition(sf::Vector2f(position.x - radius, position.y - radius));
}

void Player::Render(sf::RenderWindow* window) 
{
    window->draw(box);
    window->draw(player);
}

void Player::ScreenBoundsCollision() 
{
    if (position.x + radius > screenSize.x - borderSize) {
        position.x = screenSize.x - radius - borderSize;
        velocity.x = 0.0f;
    }
    if (position.x - radius < 0.0f + borderSize) {
        position.x = 0.0f + radius + borderSize;
        velocity.x = 0.0f;
    }

    if (position.y + radius > screenSize.y - borderSize) {
        position.y = screenSize.y - radius - borderSize;
        velocity.y = 0.0f;
        projectedVelocity.y = 0.0f;
    }
    if (position.y - radius < 0.0f + borderSize) {
        position.y = 0.0f + radius + borderSize;
        velocity.y = 0.0f;
        projectedVelocity.y = 0.0f;
    }
}

bool Player::CollisionBoxTest()
{
    if (position.x + radius > x && position.x - radius < x + w &&
        position.y + radius > y && position.y - radius < y + h)
    {
        float left = (position.x + radius) - x;
        float right = (x + w) - (position.x - radius);
        float top = (position.y + radius) - y;
        float bottom = (y + h) - (position.y - radius);

        float minX = (left < right) ? left : right;
        float minY = (top < bottom) ? top : bottom;

        if (minX < minY)
        {
            if (left < right)
                position.x = x - radius;
            else
                position.x = x + w + radius;

            velocity.x = 0.0f;
        }
        else
        {
            if (top < bottom)
                position.y = y - radius;
            else
                position.y = y + h + radius;

            velocity.y = 0.0f;
            projectedVelocity.y = 0.0f;
        }

        return true;
    }

    return false;
}