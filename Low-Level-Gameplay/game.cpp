#include "game.h"

Game::Game(sf::Vector2u screen)
{
    this->screen = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y << std::endl;

    player = new Player(screen);
    collisions = { 
        new Block(originPoint, 350.0f, 625.0f, 23.0f * 9.0f, 23.0f),
        new Block(originPoint, 260.0f, 465.0f, 23.0f * 6.0f, 23.0f),
        new Block(originPoint, 70.0f, 550.0f, 23.0f * 3.5f, 23.0f),
        new Block(originPoint, 140.0f, 225.0f, 23.0f * 3.5f, 23.0f),
        new Block(originPoint, 340.0f, 150.0f, 23.0f * 7.0f, 23.0f),
        new ScreenBounds(originPoint)
    };

    background = new sf::Texture("../Images/bombjackbg.png");
    backgroundSprite = new sf::Sprite(*background);
    backgroundSprite->setPosition(originPoint);
}

Game::~Game()
{
    delete player;
    player = nullptr;

    for (int i = 0; i < collisions.size(); i++) {
        delete collisions[i];
        collisions[i] = nullptr;
    }

    delete background;
    background = nullptr;

    delete backgroundSprite;
    backgroundSprite = nullptr;
}

void Game::Update(float deltaTime)
{
    player->Update(deltaTime);

    bool isGrounded = false;
    for (int i = 0; i < collisions.size(); i++) {
        if (collisions[i]->Collision(player))
            isGrounded = true;
    }
    // COYOTE TIME
    if (isGrounded) player->groundedBuffer = 0.01f;
    else player->groundedBuffer -= deltaTime;

    player->isGrounded = player->groundedBuffer > 0.0f;
}

void Game::Render(sf::RenderWindow* window)
{
    if (backgroundSprite != nullptr) { window->draw(*backgroundSprite); }
    player->Render(window);
    for (int i = 0; i < collisions.size(); i++)
        collisions[i]->Render(window);
}