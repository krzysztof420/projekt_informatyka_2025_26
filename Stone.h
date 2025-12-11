#ifndef STONE_H
#define STONE_H

#include <SFML/Graphics.hpp>

class Stone {
private:
    int hitpoints;
    sf::RectangleShape shape;

    sf::Color getColorForHP(int hp) {
        switch (hp) {
        case 5: return sf::Color(127, 0, 0);
        case 4: return sf::Color(159, 0, 0);
        case 3: return sf::Color(191, 0, 0);
        case 2: return sf::Color(223, 0, 0);
        case 1: return sf::Color(255, 0, 0);
        default: return sf::Color::White;
        }
    };

public:
    Stone(float cx, float cy, float w, float h, int hp)
        : hitpoints(hp)
    {
        shape.setSize({ w, h });
        shape.setOrigin(w / 2.f, h / 2.f);
        shape.setPosition(cx, cy);
        shape.setFillColor(getColorForHP(hp));
    }

    void damage(int d = 1)
    {
        if (hitpoints > 0)
        {
            hitpoints--;
            shape.setFillColor(getColorForHP(hitpoints));
        }
    }
    bool destroyed() const { return hitpoints <= 0; }
    int getHP() const { return hitpoints; }

    void draw(sf::RenderTarget& target) { target.draw(shape); }
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

    float getX() const { return shape.getPosition().x; }
    float getY() const { return shape.getPosition().y; }
};

#endif