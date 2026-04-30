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

    logo = std::make_unique<sf::Sprite>(*LoadResource("../Images/bombjack_logo.png"));
    logo->setPosition(sf::Vector2f(screen.x / 2.0f - 175.0f, (screen.y / 2.0f - 75.0f) - 200.0f));

    gameOver = std::make_unique<sf::Sprite>(*LoadResource("../Images/game-over.png"));
    gameOver->setPosition(sf::Vector2f(screen.x / 2.0f - 90.0f, screen.y / 2.0f - 69.0f));

    start.resize(2);
    start[0] = std::make_unique<sf::Sprite>(*LoadResource("../Images/start_1.png"));
    start[1] = std::make_unique<sf::Sprite>(*LoadResource("../Images/start_2.png"));

    if (!font.openFromFile("../font.ttf"))
        std::cout << "Failed to load font\n";

    text = std::make_unique<sf::Text>(font);

    text->setCharacterSize(30);
    text->setFillColor(sf::Color::White);
    text->setStyle(sf::Text::Bold);
    text->setOutlineThickness(3.0f);
    text->setString(std::string("Press Space to play!"));

    sf::FloatRect textRect = text->getLocalBounds();
    text->setOrigin(textRect.getCenter());
    text->setPosition(sf::Vector2f(screen.x / 2.0f, screen.y / 2.0f));

    scoreText = std::make_unique<sf::Text>(font);

    scoreText->setCharacterSize(30);
    scoreText->setFillColor(sf::Color::White);
    scoreText->setStyle(sf::Text::Bold);

    backgroundSprite = std::make_unique<sf::Sprite>(*LoadResource("../Images/gradient.png"));
    backgroundSprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(10, 10)));
    backgroundSprite->setScale(sf::Vector2f(63.0f, 96.0f));
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
    runtime -= deltaTime;
    if (state == State::HOME) 
    {
        gradientRuntime += deltaTime;
        if (gradientRuntime >= 9.9f) { gradientRuntime = 0.0f; }

        backgroundSprite->setTextureRect(sf::IntRect(sf::Vector2i(10.0f * gradientRuntime, 0.0f), sf::Vector2i(10, 10)));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            std::cout << "# WAITING_FOR_NEXT_LEVEL STATE" << std::endl;
            state = State::WAITING_FOR_NEXT_LEVEL;

            levelCount = 0;
            scoreManager->Reset();
        }
    }
    if (state == State::GAMEPLAY || state == State::WAITING_FOR_LEVEL_START) 
    {
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

                start[0]->setPosition(sf::Vector2f(((screen.x / 2.0f) - 84.0f) - 200.0f + (400.0f * std::clamp((2.0f - runtime), 0.0f, .5f)), (screen.y / 2.0f) - 18.0f));
                start[1]->setPosition(sf::Vector2f(((screen.x / 2.0f) - 84.0f) + 200.0f - (400.0f * std::clamp((2.0f - runtime), 0.0f, .5f)), (screen.y / 2.0f) - 18.0f));
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
                scoreManager->Death();
            }

            if ((std::count(player->freeze.begin(), player->freeze.end(), Player::FreezeState::DEATH) > 0) && runtime <= 0.0f && loadSceneBuffer) {
                loadSceneBuffer = false;

                if (scoreManager->lives <= 0) {
                    runtime = 5.0f;
                    std::cout << "# SCORE STATE" << std::endl;
                    state = State::SCORE; // Show score.

                    scoreText->setString(std::string("Score: ") + std::to_string(scoreManager->score));

                    sf::FloatRect textRect = scoreText->getLocalBounds();
                    scoreText->setOrigin(textRect.getCenter());
                    scoreText->setPosition(sf::Vector2f(screen.x / 2.0f, screen.y / 2.0f));
                }
                else {
                    std::cout << "# Respawn!" << std::endl;
                    std::cout << "# WAITING_FOR_LEVEL_START STATE" << std::endl;
                    runtime = 2.0f;
                    state = State::WAITING_FOR_LEVEL_START;
                }

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
        if (levelCount - 1 >= levelLib.size()) {
            runtime = 5.0f;
            std::cout << "# SCORE STATE" << std::endl;
            state = State::SCORE;

            scoreText->setString(std::string("Score: ") + std::to_string(scoreManager->score));

            sf::FloatRect textRect = scoreText->getLocalBounds();
            scoreText->setOrigin(textRect.getCenter());
            scoreText->setPosition(sf::Vector2f(screen.x / 2.0f, screen.y / 2.0f));
        }
        else {
            InitialiseNewLevel(levelLib[levelCount - 1]);
            std::cout << "# WAITING_FOR_LEVEL_START STATE" << std::endl;
            runtime = 2.0f;
            state = State::WAITING_FOR_LEVEL_START;
        }
    }
    if (state == State::SCORE) 
    {
        if (runtime <= 0.0f) {
            std::cout << "# HOME STATE" << std::endl;
            state = State::HOME;
        }
    }
}

void Game::Render(sf::RenderWindow* window)
{
    if (state == State::HOME)
    {
        window->draw(*backgroundSprite);
        window->draw(*logo);
        window->draw(*text);
    }
    if (state == State::GAMEPLAY || state == State::WAITING_FOR_LEVEL_START)
    {
        scoreManager->Render(window);

        if (lvl != nullptr) lvl->Render(window);

        pickupManager->Render(window);
        entityManager->Render(window);

        player->Render(window);

        if (state == State::WAITING_FOR_LEVEL_START)
        {
            for (auto& img : start) {
                window->draw(*img);
            }
        }
    }

    if (state == State::SCORE) {
        window->draw(*scoreText);
    }

    if ((std::count(player->freeze.begin(), player->freeze.end(), Player::FreezeState::DEATH) > 0) && scoreManager->lives <= 0) {
        window->draw(*gameOver);
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
