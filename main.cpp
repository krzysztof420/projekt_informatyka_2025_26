#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "GameState.h"

enum class GameStateEnum { Menu, Playing, Exiting };

int main()
{
    const float WIDTH = 640.f, HEIGHT = 480.f;
    sf::RenderWindow window(sf::VideoMode((unsigned)WIDTH, (unsigned)HEIGHT), "Arkanoid");
    window.setFramerateLimit(60);

    Game game;
    GameStateEnum currentState = GameStateEnum::Playing; // start od razu dla testu

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (event.key.code == sf::Keyboard::F5)
                {
                    GameState gs;
                    gs.capture(game.getPaddle(), game.getBall(), game.getBlocks());
                    if (gs.saveToFile("zapis.txt")) std::cout << "Gra zapisana!\n";
                    else std::cout << "B³¹d zapisu!\n";
                }
            }
        }

        // Sterowanie
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) game.getPaddleRef().moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) game.getPaddleRef().moveRight();
        game.getPaddleRef().clampToBounds(WIDTH);

        if (currentState == GameStateEnum::Playing) {
            game.update(sf::seconds(1.f/60.f));
        }

        window.clear(sf::Color(20,20,30));
        game.render(window);
        window.display();
    }

    return 0;
}
