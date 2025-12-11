#include "Game.h"
#include <algorithm>
#include <iostream>

Game::Game()
    : m_paletka(400.f, 540.f, 120.f, 20.f, 9.f),
    m_pilka(408.f, 300.f, 4.f, 3.f, 8.f)
{
    generateDefaultBlocks();
    m_fontLoaded = m_font.loadFromFile("arial.ttf");
    m_score = 0;
}

void Game::generateDefaultBlocks()
{
    m_bloki.clear();
    const int cols = 10;
    const int rows = 5;
    const float spacing = 4.f;
    const float margin = 20.f;
    float usable = m_width - 2.f * margin;
    float totalSpacing = (cols - 1) * spacing;
    float blockW = (usable - totalSpacing) / cols;
    float blockH = blockW / 2.f;
    float startX = margin + blockW / 2.f;
    float startY = 4.f + blockH / 2.f;

    for (int r = 0; r < rows; ++r) {
        int hp = rows - r;
        for (int c = 0; c < cols; ++c) {
            float cx = startX + c * (blockW + spacing);
            float cy = startY + r * (blockH + spacing);
            m_bloki.emplace_back(cx, cy, blockW, blockH, hp);
        }
    }
}

void Game::update(sf::Time /*dt*/)
{
    if (m_gameOver) return;

    m_paletka.clampToBounds(m_width);

    m_pilka.move();
    int code = m_pilka.collideWalls(m_width, m_height);
    if (code & 1) std::cout << "HIT X-WALL\n";
    if (code & 2) std::cout << "HIT Y-WALL\n";

    if (m_pilka.collidePaddle(m_paletka)) {
        std::cout << "HIT PADDLE\n";
    }

    for (auto& s : m_bloki) {
        if (!s.destroyed()) {
            sf::FloatRect b = s.getBounds();
            if (m_pilka.getX() + m_pilka.getRadius() < b.left) continue;
            if (m_pilka.getX() - m_pilka.getRadius() > b.left + b.width) continue;
            if (m_pilka.getY() + m_pilka.getRadius() < b.top) continue;
            if (m_pilka.getY() - m_pilka.getRadius() > b.top + b.height) continue;

            s.damage(1);
            m_pilka.bounceY();
            if (s.destroyed())
                m_score++;
            break;
        }
    }

    m_bloki.erase(std::remove_if(m_bloki.begin(), m_bloki.end(),
        [](const Stone& s) { return s.destroyed(); }),
        m_bloki.end());

    if (m_pilka.getY() - m_pilka.getRadius() > m_height) {
        m_gameOver = true;
        return;
    }
}

void Game::render(sf::RenderTarget& target)
{
    m_paletka.draw(target);
    m_pilka.draw(target);
    for (auto& s : m_bloki)
        s.draw(target);
    if (m_fontLoaded) {
        sf::Text scoreText;
        scoreText.setFont(m_font);
        scoreText.setString("Score: " + std::to_string(m_score));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        float centerX = m_width / 2.f;
        float textY = m_paletka.getY() + (m_paletka.getWysokosc() / 2.f) + 20.f;
        sf::FloatRect bounds = scoreText.getLocalBounds();
        scoreText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

        scoreText.setPosition(centerX, textY);
        target.draw(scoreText);
    }

    if (m_gameOver && m_fontLoaded) {
        sf::Text gameOver;
        gameOver.setFont(m_font);
        gameOver.setString("GAME OVER\n");
        gameOver.setCharacterSize(32);
        gameOver.setFillColor(sf::Color::Red);

        sf::FloatRect r = gameOver.getLocalBounds();
        gameOver.setOrigin(r.width / 2.f, r.height / 2.f);
        gameOver.setPosition(400.f, 260.f);

        target.draw(gameOver);
    }
}

void Game::reset()
{
    m_paletka.setPosition(sf::Vector2f(m_width / 2.f, 540.f));
    m_pilka.reset(sf::Vector2f(m_width / 2.f + 8.f, 300.f), sf::Vector2f(4.f, 3.f));

    generateDefaultBlocks();

    m_gameOver = false;
    m_score = 0;
}