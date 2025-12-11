#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(unsigned windowW, unsigned windowH);
    void moveUp();
    void moveDown();
    int getSelectedItem() const { return m_selected; }
    void draw(sf::RenderTarget& target);

private:
    std::vector<std::string> m_items;
    int m_selected;
    unsigned m_w, m_h;
    sf::Font m_font;
    bool m_haveFont;
};

#endif
