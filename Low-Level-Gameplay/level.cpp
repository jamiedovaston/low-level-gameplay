#include "level.h"

Level::Level(std::string levelPath)
{
    // FILE STREAM
    nlohmann::json json = nlohmann::json::parse(std::ifstream{ levelPath });

    // ORIGIN POINT
    originPoint = sf::Vector2f(json["origin"][0], json["origin"][1]);
    
    // LEVEL
    for (nlohmann::json j : json["map"]) {
        std::string type = j["type"];

        if (type == "Block") {
            collisions.push_back(new Block(originPoint, json["block"], j["rect"][0], j["rect"][1], 23.0f * j["rect"][2], 23.0f * j["rect"][3]));
        }
        else if (type == "ScreenBounds") {
            collisions.push_back(new ScreenBounds(originPoint, json["border"]));
        }
        else if (type == "SpawnPoint") {
            collisions.push_back(new SpawnPoint(originPoint, j["position"][0], j["position"][1], j["isRight"]));
        }
        else std::cout << "(!) Insufficient block type! : " << type << " (!)" << std::endl;
    }

    enemyList = json["enemies"];

    for (nlohmann::json j : json["bombs"]) {
        bombs.push_back(sf::Vector2f(j["position"][0], j["position"][1]));
    }

    // BACKGROUND
    backgroundSprite = std::make_unique<sf::Sprite>(*LoadResource(json["background"]));
    backgroundSprite->setPosition(originPoint);
}

Level::~Level()
{
    for (Collider* col : collisions) {
        delete col;
        col = nullptr;
    }
    collisions.clear();
}

void Level::Update(float deltaTime)
{

}

void Level::Render(sf::RenderWindow* window)
{
    if (backgroundSprite != nullptr) { window->draw(*backgroundSprite); }
    for (int i = 0; i < collisions.size(); i++)
        collisions[i]->Render(window);
}
