#include "Label.h"

Label::Label(const string& font_path, sf::Color color, const string& information, int sz, int x, int y): information(information), sz(sz), x(x), y(y) {
    if (!font.loadFromFile(font_path))
    {
        cout << "No font available\n";
    }

    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString(information);
    text.setCharacterSize(sz);
    text.setPosition(float(x), float(y));
}

void Label::setFillColor(sf::Color newColor) {
    text.setFillColor(newColor);
}

void Label::draw(sf::RenderWindow &window) {
    window.draw(text);
}

Label::~Label() = default;
