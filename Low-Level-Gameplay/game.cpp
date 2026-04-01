#include "game.h"

Game::Game(sf::Vector2u screen)
{
    this->screen = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y << std::endl;

    player = new Player(screen);
    level = new Level(player, "../Data/Levels/level.json");

    sf::Font font("../font.ttf");
    text = new sf::Text(font);
    text->setString("Helllooooo!");

    text->setCharacterSize(24);
    text->setFillColor(sf::Color::Red);
    text->setStyle(sf::Text::Bold | sf::Text::Underlined);
}

Game::~Game()
{
    delete level;
    level = nullptr;

    delete player;
    player = nullptr;

    delete text;
    text = nullptr;
}

void Game::Update(float deltaTime)
{
    level->Update(deltaTime);
    player->Update(deltaTime);
}

void Game::Render(sf::RenderWindow* window)
{
    level->Render(window);
    player->Render(window);

    window->draw(*text);
}