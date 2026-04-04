#include "game.h"

Game::Game(sf::Vector2u screen)
{
    this->screen = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y << std::endl;

    player = new Player(screen);

    lvl = new Level("../Data/Levels/level.json");

	entityManager = new EntityManager();
    entityManager->Spawn(lvl, new Skeleton(screen), sf::Vector2f(400.0f, 100.0f));

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

    delete entityManager;
	entityManager = nullptr;

    delete text;
	text = nullptr;

    delete lvl;
    lvl = nullptr;
}

void Game::Update(float deltaTime)
{
    lvl->Update(deltaTime);
    player->Update(deltaTime);

    for (int i = 0; i < lvl->collisions.size(); i++) {
        lvl->collisions[i]->Collision(player);
    }

    entityManager->Update(deltaTime);

    runtime += deltaTime;

    if (runtime >= 5.0f) {
		runtime = 0.0f;
		entityManager->Spawn(lvl, new Skeleton(screen), sf::Vector2f(400.0f, 100.0f));
    }
}

void Game::Render(sf::RenderWindow* window)
{
    lvl->Render(window);

	entityManager->Render(window);

    player->Render(window);

    text->setString(std::string("Runtime: ") + std::to_string(runtime));
    window->draw(*text);
}

