#include "Label.h"

Label::Label(const std::string &font_path, sf::Color color, const std::string &information, int sz, int x, int y) : information(information), sz(sz), x(x), y(y) {
    if (!font.loadFromFile(font_path)) {
        std::cout << "No font available\n";
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
void Label::setNewText(const std::string &newText) {
    text.setString(newText);
}


Label::~Label() = default;
