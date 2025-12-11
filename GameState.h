#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "BlockData.h"
#include "Game.h"
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"

class GameState {
public:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

    void capture(const Paletka& paddle, const Pilka& ball, const std::vector<Stone>& stones);
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    void apply(Game& game, Paletka& paddle, Pilka& ball, std::vector<Stone>& stones);
};

#endif
