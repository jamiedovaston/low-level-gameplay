#include "game.h"

Game::Game(sf::Vector2u screen)
{
    screenSize = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y;

    player = new Player(screen);
    collisions = { new Block(screen, screen.x / 2, screen.y / 2), new ScreenBounds(screen) };

    background = new sf::Texture("../Images/bombjackbg.png");
    backgroundSprite = new sf::Sprite(*background);
}

Game::~Game()
{
    delete player;
    player = nullptr;
}

void Game::Update(float deltaTime)
{
    player->Update(deltaTime);

    bool isGrounded = false;
    for (int i = 0; i < collisions.size(); i++) {
        if (collisions[i]->Collision(player))
            isGrounded = true;
    }
    player->isGrounded = isGrounded;
}

void Game::Render(sf::RenderWindow* window)
{
    if (backgroundSprite != nullptr) { window->draw(*backgroundSprite); }
    player->Render(window);
    for (int i = 0; i < collisions.size(); i++)
        collisions[i]->Render(window);
}