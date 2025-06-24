//
// Created by dakus on 06/05/2025.
//

#include "Button.h"

#include <iostream>
#include <bits/ostream.tcc>
#include <utility>

Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Font &font,std::string string, sf::Color textColor) : m_text(nullptr){
    m_shape.setSize(size);
    m_shape.setPosition(position);
    m_shape.setFillColor(color);
    m_shape.setOrigin(size.x / 2, size.y / 2);
    m_text = new Texte(font, position, 20, textColor, std::move(string), "Button");
}

Button::~Button() {
    delete m_text;
    std::cout << "Button delete" << std::endl;
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
    m_text->draw(window);
}

void Button::setPosition(sf::Vector2f pos) {
    m_shape.setPosition(pos);
    m_text->setPosition(pos);
}

void Button::setColor(sf::Color color) {
    m_shape.setFillColor(color);
}


sf::Vector2f Button::getPosition() const {
    return m_shape.getPosition();
}

sf::FloatRect Button::getGlobalBounds() const {
    return m_shape.getGlobalBounds();
}