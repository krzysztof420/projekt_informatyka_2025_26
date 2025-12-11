#ifndef PILKA_H
#define PILKA_H

#include <SFML/Graphics.hpp>
#include "Paletka.h"

class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float startX, float startY, float startVx, float startVy, float r)
        : x(startX), y(startY), vx(startVx), vy(startVy), radius(r)
    {
        shape.setRadius(r);
        shape.setOrigin(r, r);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }

    void move() { x += vx; y += vy; shape.setPosition(x, y); }
    void bounceX() { vx = -vx; }
    void bounceY() { vy = -vy; }

    int collideWalls(float width, float height) {
        int code = 0;
        if (x - radius <= 0.f) { x = radius; bounceX(); code |= 1; }
        else if (x + radius >= width) { x = width - radius; bounceX(); code |= 1; }

        if (y - radius <= 0.f) { y = radius; bounceY(); code |= 2; }
        shape.setPosition(x, y);
        return code;
    }

    bool collidePaddle(const Paletka& p) {
        float px = p.getX(), py = p.getY();
        float pw = p.getSzerokosc(), ph = p.getWysokosc();

        if (x > px - pw / 2 && x < px + pw / 2 && y + radius >= py - ph / 2 && y - radius < py - ph / 2)
        {
            y = py - ph / 2 - radius;
            vy = -std::abs(vy);
            shape.setPosition(x, y);
            return true;
        }
        return false;
    }

    void draw(sf::RenderTarget& target) { target.draw(shape); }

    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }

    void reset(const sf::Vector2f& pos, const sf::Vector2f& vel) {
        x = pos.x; y = pos.y; vx = vel.x; vy = vel.y;
        shape.setPosition(pos);
    }
};

#endif
