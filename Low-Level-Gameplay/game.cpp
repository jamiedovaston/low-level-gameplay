#include "game.h"

void Game::Start(sf::Vector2u screen)
{
    screenSize = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y;

    player = new Player();
    player->Start(screen);
}

void Game::Update(float deltaTime)
{
    player->Update(deltaTime);
}

void Game::Render(sf::RenderWindow* window)
{
    player->Render(window);
}