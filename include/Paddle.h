//
// Created by dakus on 05/05/2025.
//

#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Paddle {
public:
    Paddle(sf::Vector2f size, sf::Vector2f position, sf::Color color, float speed = 10.f);
    ~Paddle();
    void draw(sf::RenderWindow &window);
    void move(float dx,float dy);
    //void move(sf::Vector2f direction, float speed);
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition()const;
    sf::Vector2f getSize()const;
    sf::FloatRect getGlobalBounds()const;
    sf::RectangleShape& getShape();
    void setSpeed(float newSpeed);
    float getSpeed()const;

protected:
    float speed;
    sf::RectangleShape shape;

};



#endif //PADDLE_H
