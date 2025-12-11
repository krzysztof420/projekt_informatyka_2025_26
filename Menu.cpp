#include "Menu.h"
#include <iostream>

Menu::Menu(unsigned windowW, unsigned windowH)
    : m_selected(0), m_w(windowW), m_h(windowH)
{
    m_items = { "Start", "Load", "Exit" };
    m_haveFont = m_font.loadFromFile("arial.ttf");
}

void Menu::moveUp() {
    if (m_selected > 0) --m_selected;
}

void Menu::moveDown() {
    if (m_selected < static_cast<int>(m_items.size()) - 1) ++m_selected;
}

void Menu::draw(sf::RenderTarget& target) {
    if (m_haveFont) {
        float centerX = m_w / 2.f;
        float startY = m_h / 2.f - 90.f;
        for (size_t i = 0; i < m_items.size(); ++i) {
            sf::Text t;
            t.setFont(m_font);
            t.setString(m_items[i]);
            t.setCharacterSize(34);
            sf::FloatRect b = t.getLocalBounds();
            t.setOrigin(b.width / 2.f, b.height / 2.f);
            t.setPosition(centerX, startY + i * 70.f);
            if (static_cast<int>(i) == m_selected) t.setFillColor(sf::Color::Yellow);
            else t.setFillColor(sf::Color::White);
            target.draw(t);
        }
    }
    else {
        float w = 400.f, h = 50.f;
        float x = (m_w - w) / 2.f;
        float y = m_h / 2.f - 120.f;
        for (size_t i = 0; i < m_items.size(); ++i) {
            sf::RectangleShape rect({ w, h });
            rect.setPosition(x, y + i * 70.f);
            rect.setFillColor((static_cast<int>(i) == m_selected) ? sf::Color(220, 220, 80) : sf::Color(100, 100, 100));
            target.draw(rect);
        }
    }
}
