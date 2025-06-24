//
// Created by dakus on 06/05/2025.
//

#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Texte.h"


class Button {
public:
    Button(sf::Vector2f size, sf::Vector2f pos, sf::Color color, sf::Font &font, std::string text = "Button", sf::Color textColor = sf::Color::White);
    ~Button();
    void draw(sf::RenderWindow &window);
    void setPosition(sf::Vector2f pos);
    void setColor(sf::Color color);
    sf::Vector2f getPosition()const;
    sf::FloatRect getGlobalBounds()const;

protected:
    sf::RectangleShape m_shape;
    Texte* m_text;

};



#endif //BUTTON_H
