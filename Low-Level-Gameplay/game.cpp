#include "game.h"

void Body::Start(sf::Vector2u screen)
{
    screenSize = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y;

    player = sf::CircleShape(radius);
    position = sf::Vector2f((screen.x / 2.0f) - radius, (screen.y / 2.0f) - radius);
    player.setFillColor(sf::Color::Green);
}

void Body::Update(float deltaTime)
{
    // if (position.x + (radius * 2) >= screenSize.x)
    //     directionX = 1.0f;
    // if (position.y + (radius * 2) >= screenSize.y)
    //     directionY = 1.0f;
    // if (position.x <= 0.0f)
    //     directionX = -1.0f;
    // if (position.y <= 0.0f)
    //     directionY = -1.0f;

    float directionX = 0.0f, directionY = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
    {
        directionY += 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        directionX -= 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {

        directionY -= 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        directionX += 1.0f;
    }
    
    // Inverted Y (defaults to positives being down)
    position += sf::Vector2f(directionX, -directionY) * deltaTime * speed;
    player.setPosition(position);
}

void Body::Render(sf::RenderWindow* window)
{
    window->draw(player);
}