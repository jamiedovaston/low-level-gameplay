#include "main.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 630, 920 }), "Bombjack: Reborn!", sf::Style::Titlebar | sf::Style::Close);

    sf::Image icon;
    if(icon.loadFromFile("Images/jack.png")) window.setIcon(icon.getSize(), icon.getPixelsPtr());

    Game* game = new Game(window.getSize());

    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0.0f;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        // DELTA CALCULATIONS
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.0f;
        lastTime = now;

        game->Update(deltaTime);
        game->Render(&window);

        window.display();
    }

    delete game;
    game = nullptr;
}