#include "game.h"

Game::Game(sf::Vector2u screen)
{
    this->screen = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y << std::endl;

    player = new Player(screen);

    lvl = new Level("../Data/Levels/level.json");

    scoreManager = std::make_unique<ScoreManager>();
    entityManager = std::make_unique<EntityManager>(player, screen, scoreManager.get());
    entityManager.get()->AssignLevel(lvl);
    pickupManager = std::make_unique<PickupManager>(player, screen, scoreManager.get());

    for (sf::Vector2f p : lvl->bombs) {
        pickupManager->Spawn(lvl, new Bomb(player, screen), p);
    }

    for (auto& colPtr : lvl->collisions) {
        Collider* col = colPtr.get();

        if (auto sp = dynamic_cast<SpawnPoint*>(col)) {
            pickupManager->Spawn(lvl, new PowerUpCoin(player, screen), sp->Position());
        }
    }

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

    delete text;
	text = nullptr;

    delete lvl;
    lvl = nullptr;
}

void Game::Update(float deltaTime)
{
    runtime -= deltaTime;
    if(lvl != nullptr) lvl->Update(deltaTime);
    player->Update(deltaTime);

    if (lvl != nullptr) {
        for (int i = 0; i < lvl->collisions.size(); i++) {
            lvl->collisions[i]->Collision(player);
        }
    }

    scoreManager.get()->Update(deltaTime);
    entityManager->Update(deltaTime);
    pickupManager->Update(deltaTime);

    text->setString(std::string("Score: ") + std::to_string(scoreManager.get()->score));
    
    if (player->isDead && runtime <= 0.0f && !playerDeadBuffer) {
        playerDeadBuffer = true;
        runtime = 5.0f;
    }

    if (player->isDead && runtime <= 0.0f && playerDeadBuffer) {
        playerDeadBuffer = false;
        player->isDead = false;

        std::cout << "Respawn!" << std::endl;

        entityManager.get()->Clear(lvl);
        scoreManager.get()->NewRound();

        player->Respawn();
    }

    if (pickupManager.get()->bombCount <= 0)
    {
        entityManager.get()->Clear(lvl);
        pickupManager.get()->Clear(lvl);

        delete lvl;
        lvl = nullptr;

        lvl = new Level("../Data/Levels/level.json");
        entityManager.get()->AssignLevel(lvl);

        scoreManager.get()->NewRound();

        for (sf::Vector2f p : lvl->bombs) {
            pickupManager->Spawn(lvl, new Bomb(player, screen), p);
        }

        player->Respawn();
    }
}

void Game::Render(sf::RenderWindow* window)
{
    if(lvl != nullptr) lvl->Render(window);

	entityManager->Render(window);
    pickupManager->Render(window);

    player->Render(window);

    window->draw(*text);
}
