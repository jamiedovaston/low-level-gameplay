#include "game.h"

Game::Game(sf::Vector2u screen)
{
    this->screen = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y << std::endl;

    player = new Player(screen);

    scoreManager = std::make_unique<ScoreManager>(player);
    entityManager = std::make_unique<EntityManager>(player, screen, scoreManager.get());
    pickupManager = std::make_unique<PickupManager>(player, screen, scoreManager.get());
    
    state = State::HOME;
    std::cout << "# HOME STATE" << std::endl;

    logo = new sf::Sprite(*LoadResource("../Images/bombjack_logo.png"));
    logo->setPosition(sf::Vector2f(screen.x / 2.0f - 175.0f, (screen.y / 2.0f - 75.0f) - 200.0f));

    if (!font.openFromFile("../font.ttf"))
        std::cout << "Failed to load font\n";

    text = std::make_unique<sf::Text>(font);
    text->setFont(font);

    text->setCharacterSize(30);
    text->setFillColor(sf::Color::White);
    text->setStyle(sf::Text::Bold);
    text->setPosition(sf::Vector2f(screen.x / 2.0f - 175.0f, (screen.y / 2.0f - 75.0f)));

    text->setString(std::string("Press Space to play!"));
}

Game::~Game()
{
    delete player;
    player = nullptr;

    delete lvl;
    lvl = nullptr;
}

void Game::Update(float deltaTime)
{
    if (state == State::HOME) 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            std::cout << "# WAITING_FOR_NEXT_LEVEL STATE" << std::endl;
            state = State::WAITING_FOR_NEXT_LEVEL;

            levelCount = 0;
            scoreManager->Reset();
        }
    }
    if (state == State::GAMEPLAY || state == State::WAITING_FOR_LEVEL_START) 
    {
        runtime -= deltaTime;
        if (lvl != nullptr) lvl->Update(deltaTime);
        player->Update(deltaTime);

        if (lvl != nullptr) {
            for (int i = 0; i < lvl->collisions.size(); i++) {
                lvl->collisions[i]->Collision(player);
            }
        }

        scoreManager->Update(deltaTime);
        entityManager->Update(deltaTime);
        pickupManager->Update(deltaTime);

        if (state == State::WAITING_FOR_LEVEL_START) 
        {
            if (runtime > 0.0f) {
                if ((std::count(player->freeze.begin(), player->freeze.end(), Player::FreezeState::WAITING_TO_START) <= 0)) {
                    player->freeze.push_back(Player::FreezeState::WAITING_TO_START);
                }
            }
            else if ((std::count(player->freeze.begin(), player->freeze.end(), Player::FreezeState::WAITING_TO_START) > 0)) {
                player->freeze.clear();
                std::cout << "# GAMEPLAY STATE" << std::endl;
                state = State::GAMEPLAY;
            }
        }

        if (state == State::GAMEPLAY) 
        {
            if ((std::count(player->freeze.begin(), player->freeze.end(), Player::FreezeState::DEATH) > 0) && !loadSceneBuffer) {
                loadSceneBuffer = true;
                runtime = 5.0f;
            }

            if ((std::count(player->freeze.begin(), player->freeze.end(), Player::FreezeState::DEATH) > 0) && runtime <= 0.0f && loadSceneBuffer) {
                loadSceneBuffer = false;

                std::cout << "# Respawn!" << std::endl;
        
                entityManager->Clear();
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
                player->freeze.clear();

                std::cout << "# Load new level!" << std::endl;

                std::cout << "# WAITING_FOR_NEXT_LEVEL STATE" << std::endl;
                state = State::WAITING_FOR_NEXT_LEVEL;
            }
        }
    }
    if (state == State::WAITING_FOR_NEXT_LEVEL) 
    {
        levelCount++;
        if (levelCount - 1 == levelLib.size()) {
            state = State::HOME;
            std::cout << "# HOME STATE" << std::endl;
        }
        else {
            InitialiseNewLevel(levelLib[levelCount - 1]);
            std::cout << "# WAITING_FOR_LEVEL_START STATE" << std::endl;
            runtime = 3.0f;
            state = State::WAITING_FOR_LEVEL_START;
        }
    }
}

void Game::Render(sf::RenderWindow* window)
{
    if (state == State::HOME) 
    {
        window->draw(*logo);
        window->draw(*text);
    }
    if (state == State::GAMEPLAY || state == State::WAITING_FOR_LEVEL_START)
    {
        scoreManager->Render(window);

        if(lvl != nullptr) lvl->Render(window);

        pickupManager->Render(window);
	    entityManager->Render(window);

        player->Render(window);
    }
}

void Game::InitialiseNewLevel(std::string filePath)
{
    if (lvl != nullptr) {
        entityManager->Clear();
        pickupManager->Clear();
        delete lvl;
    }

    lvl = new Level(filePath);
    entityManager->AssignLevel(lvl);
    pickupManager->AssignLevel(lvl);

    scoreManager->NewRound();

    for (sf::Vector2f p : lvl->bombs) {
        pickupManager->Spawn(new Bomb(player, screen), p);
    }

    player->Respawn();
}
