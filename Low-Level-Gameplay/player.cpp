#include "player.h"

void Player::Start(sf::Vector2u screen) 
{
    screenSize = screen;

    // CREATE PLAYER
    player = sf::CircleShape(radius);
    // SPAWN AT POSITION
    position = sf::Vector2f((screen.x / 2.0f) - radius, (screen.y / 2.0f) - radius);
    // SET COLOUR
    player.setFillColor(sf::Color::Green);
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

    // INPUT * SPEED
    velocity += direction * speed;

    // GRAVITY
    velocity.y += gravity;

    // INVERT VELOCITY Y (defaults to downwards being positive) AND ADDS TO POSITION
    position += sf::Vector2f(velocity.x, -velocity.y) * deltaTime;

    // KEEP BALL IN SCREEN BOUNDS (0, 0 is top left)
    ScreenBoundsCollision();

    player.setPosition(position);
}

void Player::Render(sf::RenderWindow* window) 
{
    window->draw(player);
}

void Player::ScreenBoundsCollision() 
{
    if (position.x + (radius * 2) > screenSize.x) {
        position.x = screenSize.x - (radius * 2);
        velocity.x = 0.0f;
    }
    if (position.x < 0.0f) {
        position.x = 0.0f;
        velocity.x = 0.0f;
    }

    if (position.y + (radius * 2) > screenSize.y) {
        position.y = screenSize.y - (radius * 2);
        velocity.y = 0.0f;
    }
    if (position.y < 0.0f) {
        position.y = 0.0f;
        velocity.y = 0.0f;
    }
}