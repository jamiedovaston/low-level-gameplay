#include "game.h"

Game::Game(sf::Vector2u screen)
{
    this->screen = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y << std::endl;

    player = new Player(screen);

    enemies = {
		new Enemy(screen)
	};

    std::vector<Entity*> e = {
        player
    };

    e.insert(e.end(), enemies.begin(), enemies.end());

    lvl = new Level(e, "../Data/Levels/level.json");

    if (!font.openFromFile("../font.ttf"))
        std::cout << "Failed to load font\n";

	text = new sf::Text(font);

    text->setFont(font);

    text->setCharacterSize(60);
    text->setFillColor(sf::Color::White);
    text->setStyle(sf::Text::Bold);
    text->setPosition(sf::Vector2f(10.0f, 10.0f));
}

Game::~Game()
{
    delete player;
    player = nullptr;

    for (int i = 0; i < enemies.size(); i++) {
		delete enemies[i];
    }
    enemies.clear();

    delete text;
	text = nullptr;

    delete lvl;
    lvl = nullptr;
}

void Game::Update(float deltaTime)
{
    lvl->Update(deltaTime);
    player->Update(deltaTime);

    for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Update(deltaTime);
    }

    runtime += deltaTime;
}

void Game::Render(sf::RenderWindow* window)
{
    lvl->Render(window);
    player->Render(window);

    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->Render(window);
    }

    text->setString(std::string("Runtime: ") + std::to_string(runtime));
    window->draw(*text);
}