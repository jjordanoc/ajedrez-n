#ifndef PROYECTOPROGRA2_LABEL_H
#define PROYECTOPROGRA2_LABEL_H

#include <iostream>
#include <SFML/Graphics.hpp>


class Label {
private:
    sf::Color color;
    sf::Font font;
    std::string information;
    int sz{};
    int x{};
    int y{};

    sf::Text text;  // main text
public:
    Label() = default;
    Label(const std::string& font_path, sf::Color color, const std::string& information, int sz, int x, int y);

    void draw(sf::RenderWindow &window);
    void setFillColor(sf::Color newColor);
    void setNewText(const std::string& newText);

    virtual ~Label();
};


#endif //PROYECTOPROGRA2_LABEL_H
