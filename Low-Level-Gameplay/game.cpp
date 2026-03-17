#include "game.h"

Game::Game(sf::Vector2u screen)
{
    screenSize = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y;

    border = new sf::Texture("../Images/Border.png");
    sprite = new sf::Sprite(*border);

    player = new Player(screen);
    player->Start();
}

Game::~Game()
{
    delete border;
    border = nullptr;

    delete sprite;
    sprite = nullptr;
}

void Game::Update(float deltaTime)
{
    player->Update(deltaTime);
}

void Game::Render(sf::RenderWindow* window)
{
    player->Render(window);
    if (sprite != nullptr) { window->draw(*sprite); }


}