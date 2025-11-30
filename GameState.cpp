#include "GameState.h"
#include <fstream>
#include <iostream>

void GameState::capture(const Paletka& paddle, const Pilka& ball, const std::vector<Stone>& stones)
{
    paddlePosition = sf::Vector2f(paddle.getX(), paddle.getY());
    ballPosition = sf::Vector2f(ball.getX(), ball.getY());
    ballVelocity = sf::Vector2f(ball.getVx(), ball.getVy());

    blocks.clear();
    blocks.reserve(stones.size());
    for (const auto& s : stones) {
        BlockData b{ s.getX(), s.getY(), s.getHP() };
        blocks.push_back(b);
    }
}

bool GameState::saveToFile(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
         << ballVelocity.x << " " << ballVelocity.y << "\n";
    file << "BLOCKS_COUNT " << blocks.size() << "\n";
    for (const auto& b : blocks)
        file << b.x << " " << b.y << " " << b.hp << "\n";
    file.close();
    return true;
}

bool GameState::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) { std::cerr << "Nie mo¿na otworzyæ pliku save!\n"; return false; }

    std::string label;
    if (!(file >> label >> paddlePosition.x >> paddlePosition.y)) return false;
    if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y)) return false;

    int blockCount = 0;
    if (!(file >> label >> blockCount)) return false;

    blocks.clear();
    blocks.reserve(blockCount);
    for (int i = 0; i < blockCount; i++) {
        BlockData bd;
        if (!(file >> bd.x >> bd.y >> bd.hp)) return false;
        blocks.push_back(bd);
    }
    file.close();
    return true;
}

void GameState::apply(Paletka& p, Pilka& b, std::vector<Stone>& stones)
{
    p.setPosition(paddlePosition);
    b.reset(ballPosition, ballVelocity);

    stones.clear();
    const float BLOCK_W = 60.f;
    const float BLOCK_H = 25.f;
    for (const auto& bd : blocks) {
        stones.emplace_back(bd.x, bd.y, BLOCK_W, BLOCK_H, bd.hp);
    }
}
