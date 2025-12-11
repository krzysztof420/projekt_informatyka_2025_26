#include "Game.h"
#include "GameState.h"
#include <fstream>
#include <iostream>

void GameState::capture(Game& game,const Paletka& paddle, const Pilka& ball, const std::vector<Stone>& stones)
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
    score = game.getScore();
}

bool GameState::saveToFile(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " " << ballVelocity.x << " " << ballVelocity.y << "\n";
    file << "BLOCKS_COUNT " << blocks.size() << "\n";
    for (const auto& b : blocks)
        file << b.x << " " << b.y << " " << b.hp << "\n";
    file << "SCORE " << score << "\n";
    file.close();
    return true;
}

bool GameState::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())  return false;

    std::string label;
    if (!(file >> label >> paddlePosition.x >> paddlePosition.y)) return false;
    if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y)) return false;

    int blockCount;
    if (!(file >> label >> blockCount)) return false;

    blocks.clear();
    for (int i = 0; i < blockCount; i++) {
        BlockData bd;
        if (!(file >> bd.x >> bd.y >> bd.hp)) return false;
        blocks.push_back(bd);
    }
    blocks.reserve(blockCount);

    file >> label >> score;

    file.close();
    return true;
}

void GameState::apply(Game& g, Paletka& p, Pilka& b, std::vector<Stone>& stones)
{
    p.setPosition(paddlePosition);
    b.reset(ballPosition, ballVelocity);

    const float BLOCK_W = ((800.f - 2.f * 20.f) - (10 - 1) * 4.f) / 10.f;
    const float BLOCK_H = BLOCK_W / 2.f;

    stones.clear();
    stones.reserve(blocks.size());
    sf::Color blockColor(200, 80, 80);
    for (const auto& bd : blocks) {
        stones.emplace_back(bd.x, bd.y, BLOCK_W, BLOCK_H, bd.hp);
    }
    g.resetGameOver();
    g.setScore(score);
}
