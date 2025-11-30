#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"

class Game {
private:
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;

public:
    Game();

    void update(sf::Time dt);
    void render(sf::RenderTarget& target);

    const Paletka& getPaddle() const { return m_paletka; }
    const Pilka& getBall() const { return m_pilka; }
    const std::vector<Stone>& getBlocks() const { return m_bloki; }

    Paletka& getPaddleRef() { return m_paletka; }
    Pilka& getBallRef() { return m_pilka; }
    std::vector<Stone>& getBlocksRef() { return m_bloki; }
};

#endif // GAME_H
