#ifndef PROYECTOPROGRA2_LABEL_H
#define PROYECTOPROGRA2_LABEL_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Label {
public:
    sf::Color color;
    sf::Font font;
    string information;
    int sz{};
    int x{};
    int y{};

    sf::Text text;  // main text
public:
    Label() = default;
    Label(const string& font_path, sf::Color color, const string& information, int sz, int x, int y);

    void draw(sf::RenderWindow &window);
    void setFillColor(sf::Color newColor);

    virtual ~Label();
};


#endif //PROYECTOPROGRA2_LABEL_H
