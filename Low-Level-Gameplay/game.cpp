#include "game.h"

Game::Game(sf::Vector2u screen)
{
    this->screen = screen;

    std::cout << "X: " << screen.x << " Y: " << screen.y << std::endl;

    player = new Player(screen);

    lvl = new Level("../Data/Levels/level.json");

    scoreManager = std::make_unique<ScoreManager>();
    entityManager = std::make_unique<EntityManager>(player, screen, scoreManager.get());
    currencyManager = std::make_unique<PickupManager>(player, screen, scoreManager.get());

    for (sf::Vector2f p : lvl->bombs) {
        currencyManager->Spawn(lvl, new Bomb(player, screen), p);
    }

    for (auto& colPtr : lvl->collisions) {
        Collider* col = colPtr.get();

        if (auto sp = dynamic_cast<SpawnPoint*>(col)) {
            currencyManager->Spawn(lvl, new PowerUpCoin(player, screen), sp->Position());
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
    lvl->Update(deltaTime);
    player->Update(deltaTime);

    for (int i = 0; i < lvl->collisions.size(); i++) {
        lvl->collisions[i]->Collision(player);
    }

    entityManager->Update(deltaTime);
    currencyManager->Update(deltaTime);

    text->setString(std::string("Score: ") + std::to_string(scoreManager.get()->score));

    if(!player->isDead)
        runtime -= deltaTime;

    if (runtime <= 0.0f) {
		runtime = 5.0f;
        if (entityManager->parent[lvl].size() < lvl->enemyList.size()) 
        {
            SpawnPoint* furthest = nullptr;
            float maxDist = -1.0f;

            // GET THE FURTHEST AWAY
            for (auto& colPtr : lvl->collisions) {
                Collider* col = colPtr.get();

                if (auto sp = dynamic_cast<SpawnPoint*>(col)) {
                    float d = sp->Distance(player);

                    if (d > maxDist) {
                        maxDist = d;
                        furthest = sp;
                    }
                }
            }

            if (furthest) {
                entityManager->Spawn(lvl, new Skeleton(player, screen), furthest->Position());
            }
        }
    }
}

void Game::Render(sf::RenderWindow* window)
{
    lvl->Render(window);

	entityManager->Render(window);
    currencyManager->Render(window);

    player->Render(window);

    window->draw(*text);
}
