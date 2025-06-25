//
// Created by dakus on 06/05/2025.
//

#include "../include/Texte.h"

#include <iostream>

Texte::Texte(sf::Font &font, sf::Vector2f pos, int characterSize, sf::Color color, std::string string, std::string name) : m_name(name), m_visible(true), m_blinkInterval(3) {
    m_text.setFont(font);
    m_text.setCharacterSize(characterSize);
    m_text.setFillColor(color);
    m_text.setPosition(pos);
    setString(string);
}

Texte::~Texte() {
    std::cout << "Texte delete" << std::endl;
}

void Texte::draw(sf::RenderWindow &window) {
    window.draw(m_text);
}

void Texte::setString(std::string text) {
    m_text.setString(text);
    sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin(bounds.width / 2, bounds.height / 2);
}

void Texte::setPosition(sf::Vector2f pos) {
    m_text.setPosition(pos);
}

void Texte::setOrigin(sf::Vector2f origin) {
    m_text.setOrigin(origin);
}


void Texte::setColor(sf::Color color) {
    m_text.setFillColor(color);
}

void Texte::setCharacterSize(int size) {
    m_text.setCharacterSize(size);
}

void Texte::setFont(sf::Font &font) {
    m_text.setFont(font);
}

sf::Vector2f Texte::getPosition() const {
    return m_text.getPosition();
}