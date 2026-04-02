#include "level.h"

Level::Level(std::vector<Entity*> entities, std::string levelPath)
{
    // FILE STREAM
    nlohmann::json json = nlohmann::json::parse(std::ifstream{ levelPath });

    // ORIGIN POINT
    originPoint = sf::Vector2f(json["origin"][0], json["origin"][1]);
    
    // LEVEL
    for (nlohmann::json j : json["map"]) {
        std::string type = j["type"];

        if (type == "Block") {
            collisions.push_back(new Block(originPoint, j["rect"][0], j["rect"][1], 23.0f * j["rect"][2], 23.0f * j["rect"][3]));
        }
        else if (type == "ScreenBounds") {
            collisions.push_back(new ScreenBounds(originPoint));
        }
        else {
            std::cout << "(!) Insufficient block type! : " << type << " (!)" << std::endl;
        }
    }

    // BACKGROUND
    background = new sf::Texture(json["background"]);
    backgroundSprite = new sf::Sprite(*background);
    backgroundSprite->setPosition(originPoint);

    this->entities = entities;
}

Level::~Level()
{
    delete background;
    background = nullptr;

    delete backgroundSprite;
    backgroundSprite = nullptr;

    for (int i = 0; i < collisions.size(); i++) {
        delete collisions[i];
    }
    collisions.clear();
}

void Level::Update(float deltaTime)
{
    for (int i = 0; i < collisions.size(); i++) {
        for (int k = 0; k < entities.size(); k++) {
            collisions[i]->Collision(entities[k]);
        }
    }
}

void Level::Render(sf::RenderWindow* window)
{
    if (backgroundSprite != nullptr) { window->draw(*backgroundSprite); }
    for (int i = 0; i < collisions.size(); i++)
        collisions[i]->Render(window);
}
