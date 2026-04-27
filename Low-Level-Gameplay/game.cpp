#include "game.h"

Game::Game(sf::Vector2u screen)
{
    this->screen = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y << std::endl;

    player = new Player(screen);

    scoreManager = std::make_unique<ScoreManager>();
    entityManager = std::make_unique<EntityManager>(player, screen, scoreManager.get());
    pickupManager = std::make_unique<PickupManager>(player, screen, scoreManager.get());

    InitialiseNewLevel("../Data/Levels/level2.json");
}

Game::~Game()
{
    delete player;
    player = nullptr;
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

    scoreManager->Update(deltaTime);
    entityManager->Update(deltaTime);
    pickupManager->Update(deltaTime);

    if ((std::count(player->freeze.begin(), player->freeze.end(), Player::FreezeState::DEATH) > 0) && !loadSceneBuffer) {
        loadSceneBuffer = true;
        runtime = 5.0f;
    }

    if ((std::count(player->freeze.begin(), player->freeze.end(), Player::FreezeState::DEATH) > 0) && runtime <= 0.0f && loadSceneBuffer) {
        loadSceneBuffer = false;

        std::cout << "# Respawn!" << std::endl;

        entityManager->Clear(lvl.get());
        scoreManager->NewRound();

        player->Respawn();
    }

    if (pickupManager->bombCount <= 0 && !loadSceneBuffer) // WIN
    {
        player->freeze.push_back(Player::FreezeState::WIN);
        loadSceneBuffer = true;
        runtime = 5.0f;
    }
    if((std::count(player->freeze.begin(), player->freeze.end(), Player::FreezeState::WIN) > 0) && runtime <= 0.0f && loadSceneBuffer) {
        loadSceneBuffer = false;

        std::cout << "# Load new level!" << std::endl;

        InitialiseNewLevel("../Data/Levels/level.json");
    }
}

void Game::Render(sf::RenderWindow* window)
{
    scoreManager->Render(window);

    if(lvl != nullptr) lvl->Render(window);

    pickupManager->Render(window);
	entityManager->Render(window);

    player->Render(window);
}

void Game::InitialiseNewLevel(std::string filePath)
{
    if (lvl != nullptr) {
        entityManager->Clear(lvl.get());
        pickupManager->Clear(lvl.get());
    }

    lvl = std::make_unique<Level>(filePath);
    entityManager->AssignLevel(lvl.get());

    scoreManager->NewRound();

    for (sf::Vector2f p : lvl->bombs) {
        pickupManager->Spawn(lvl.get(), new Bomb(player, screen), p);
    }

    player->Respawn();
}
