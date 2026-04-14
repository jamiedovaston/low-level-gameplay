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
            collisions.push_back(std::make_unique<Block>(originPoint, j["rect"][0], j["rect"][1], 23.0f * j["rect"][2], 23.0f * j["rect"][3]));
        }
        else if (type == "ScreenBounds") {
            collisions.push_back(std::make_unique<ScreenBounds>(originPoint));
        }
        else {
            std::cout << "(!) Insufficient block type! : " << type << " (!)" << std::endl;
        }
    }

    // BACKGROUND
    background = std::make_unique<sf::Texture>(json["background"]);

    backgroundSprite = std::make_unique<sf::Sprite>(*background);
    backgroundSprite->setPosition(originPoint);
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
