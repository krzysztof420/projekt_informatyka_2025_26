#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Menu.h"
#include "GameState.h"

enum class AppState { MenuState, Playing, Exiting };

int main()
{
    const unsigned WIDTH = 800;
    const unsigned HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(WIDTH, HEIGHT);
    Game game;
    AppState currentState = AppState::MenuState;

    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window.close(); break; }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (currentState == AppState::Playing) currentState = AppState::MenuState;
                    else window.close();
                }

                if (currentState == AppState::MenuState) {
                    if (event.key.code == sf::Keyboard::Up) menu.moveUp();
                    else if (event.key.code == sf::Keyboard::Down) menu.moveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int sel = menu.getSelectedItem();
                        if (sel == 0) 
                        {
                            game.reset();
                            game.generateDefaultBlocks();
                            currentState = AppState::Playing;
                            deltaClock.restart();
                        }
                        else if (sel == 1) {
                            GameState gs;
                            if (gs.loadFromFile("zapis.txt")) {
                                std::cout << "Zapis wczytany!\n";
                                gs.apply(game,game.getPaddleRef(), game.getBallRef(), game.getBlocksRef());
                                currentState = AppState::Playing;
                                deltaClock.restart();
                            }
                            else {
                                std::cout << "Brak zapisu lub blad odczytu.\n";
                            }
                        }
                        else {
                            window.close();
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::F5) {
                    if (currentState == AppState::Playing) {
                        GameState gs;
                        gs.capture(game.getPaddle(), game.getBall(), game.getBlocks());
                        if (gs.saveToFile("zapis.txt")) std::cout << "Gra zapisana!\n";
                        else std::cout << "B³¹d zapisu!\n";
                    }
                }
            }
        }

        if (currentState == AppState::Playing && !game.isGameOver()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                game.getPaddleRef().moveLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                game.getPaddleRef().moveRight();
        }

        sf::Time dt = deltaClock.restart();
        if (currentState == AppState::Playing && !game.isGameOver()) game.update(dt);

        window.clear(sf::Color(20, 20, 30));
        if (currentState == AppState::MenuState) {
            menu.draw(window);
        }
        else if (currentState == AppState::Playing) {
            game.render(window);
        }
        window.display();
    }

    return 0;
}
