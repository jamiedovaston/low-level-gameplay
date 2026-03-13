#include "player.h"
#include <iostream>

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


    // INPUT * SPEED
    float projectedVelocityX = direction.x * horizontalSpeed;
    if(velocity.x + projectedVelocityX < maxHorizontalSpeed && velocity.x + projectedVelocityX > -maxHorizontalSpeed)
        velocity.x += projectedVelocityX;
    velocity += sf::Vector2f(0.0f, 1.0f) * direction.y * verticalSpeed;

    // GRAVITY
    velocity.y += gravity;
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
    if (position.x + radius > screenSize.x) {
        position.x = screenSize.x - radius;
        velocity.x = 0.0f;
    }
    if (position.x - radius < 0.0f) {
        position.x = 0.0f + radius;
        velocity.x = 0.0f;
    }

    if (position.y + radius > screenSize.y) {
        position.y = screenSize.y - radius;
        velocity.y = 0.0f;
    }
    if (position.y - radius < 0.0f) {
        position.y = 0.0f + radius;
        velocity.y = 0.0f;
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
            // Resolve X collision
            if (left < right)
                position.x = x - radius;
            else
                position.x = x + w + radius;

            velocity.x = 0.0f;
        }
        else
        {
            // Resolve Y collision
            if (top < bottom)
                position.y = y - radius;
            else
                position.y = y + h + radius;

            velocity.y = 0.0f;
        }

        return true;
    }

    return false;
}