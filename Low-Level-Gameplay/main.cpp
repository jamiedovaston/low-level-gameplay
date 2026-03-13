#include "game.h"
#include "main.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 960, 540 }), "SFML works!");

    Game* game = new Game();

    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0.0f;

    game->Start(window.getSize());

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
}