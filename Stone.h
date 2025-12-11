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
    const float m_width = 800.f;
    const float m_height = 600.f;
    bool m_gameOver = false;
    int m_score;
    sf::Font m_font;
    bool m_fontLoaded = false;
    int m_level = 1;

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

    void generateDefaultBlocks();

    bool isGameOver() const { return m_gameOver; }
    void reset();
    void resetGameOver() { m_gameOver = false; }

    int getScore() const { return m_score; }
    void setScore(int s) { m_score = s; }
    void resetScore() { m_score = 0; }

    void setLevel(int level) { m_level = level; }
    int getLevel() const { return m_level; }
};

#endif
