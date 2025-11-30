#include "Game.h"
#include <iostream>

Game::Game()
    : m_paletka(320.f, 440.f, 100.f, 28.f, 8.f),
      m_pilka(328.f, 200.f, 4.f, 3.f, 8.f)
{
    // Tworzenie bloków 10x5
    const int rows = 5, cols = 10;
    const float spacing = 4.f;
    const float screenWidth = 640.f;
    float blockW = (screenWidth - (cols + 1) * spacing) / cols;
    float blockH = blockW / 2.f;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            float x = spacing + blockW/2.f + c * (blockW + spacing);
            float y = spacing + blockH/2.f + r * (blockH + spacing);
            m_bloki.emplace_back(x, y, blockW, blockH, 1, sf::Color::Red);
        }
    }
}

void Game::update(sf::Time dt)
{
    m_pilka.move();
    m_pilka.collideWalls(640.f, 480.f);
    if (m_pilka.collidePaddle(m_paletka)) {
        std::cout << "HIT PADDLE\n";
    }

    // Bloki
    for (auto& s : m_bloki) {
        if (!s.destroyed() && m_pilka.getY() - m_pilka.getRadius() < s.getY() + 12.5f &&
            m_pilka.getY() + m_pilka.getRadius() > s.getY() - 12.5f &&
            m_pilka.getX() > s.getX() - 30.f && m_pilka.getX() < s.getX() + 30.f)
        {
            s.damage();
            m_pilka.bounceY();
        }
    }

    m_bloki.erase(std::remove_if(m_bloki.begin(), m_bloki.end(),
                                  [](const Stone& s){ return s.destroyed(); }),
                   m_bloki.end());
}

void Game::render(sf::RenderTarget& target)
{
    m_paletka.draw(target);
    m_pilka.draw(target);
    for (auto& s : m_bloki)
        s.draw(target);
}
