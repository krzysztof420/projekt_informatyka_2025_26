#ifndef STONE_H
#define STONE_H

#include <SFML/Graphics.hpp>

class Stone {
private:
    int hitpoints;
    sf::RectangleShape shape;

public:
    Stone(float cx, float cy, float w, float h, int hp = 1, sf::Color color = sf::Color::Red)
        : hitpoints(hp)
    {
        shape.setSize({w, h});
        shape.setOrigin(w/2.f, h/2.f);
        shape.setPosition(cx, cy);
        shape.setFillColor(color);
    }

    void damage(int d=1) { hitpoints -= d; }
    bool destroyed() const { return hitpoints <= 0; }
    int getHP() const { return hitpoints; }

    void draw(sf::RenderTarget& target) { target.draw(shape); }
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

    float getX() const { return shape.getPosition().x; }
    float getY() const { return shape.getPosition().y; }
};

#endif // STONE_H
