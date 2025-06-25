//
// Created by dakus on 06/05/2025.
//

#ifndef TEXTE_H
#define TEXTE_H
#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class Texte {
public:
    Texte(sf::Font &font, sf::Vector2f pos, int characterSize = 10, sf::Color color = sf::Color::White, std::string string = "None", std::string name = "NoName");
    ~Texte();

    void draw(sf::RenderWindow &window);
    void setString(std::string text);
    void setPosition(sf::Vector2f pos);
    void setOrigin(sf::Vector2f origin);
    void setColor(sf::Color color);
    void setCharacterSize(int size);
    void setFont(sf::Font &font);
    sf::Vector2f getPosition()const;

protected:
    sf::Text m_text;
    std::string m_name;
    sf::Clock m_clock;
    bool m_visible;
    float m_blinkInterval;

};



#endif //TEXTE_H
