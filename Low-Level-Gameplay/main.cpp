#include "game.h"
#include "main.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 600, 600 }), "SFML works!");

    Body* body = new Body();

    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0.0f;

    body->Start(window.getSize());

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.0f;
        lastTime = now;

        body->Update(deltaTime);
        body->Render(&window);

        window.display();
    }
}