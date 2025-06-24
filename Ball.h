//
// Created by dakus on 05/05/2025.
//

#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Paddle.h"


class Ball {
public:
    Ball(float radius, sf::Vector2f position, sf::Color color, float speed = 10.f, sf::Vector2f velocity = sf::Vector2f(1,1));
    ~Ball();
    void update(sf::RenderWindow &window, Paddle &playerPaddle, Paddle &botPaddle);
    void draw(sf::RenderWindow &window);
    void move(float dx,float dy);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition()const;
    float getRadius()const;
    sf::FloatRect getGlobalBounds()const;
    sf::CircleShape& getShape();
    void setSpeed(float newSpeed);
    float getSpeed()const;
    void setVelocity(sf::Vector2f newVelocity);
    sf::Vector2f getVelocity()const;

protected:
    float m_speed;
    sf::Vector2f m_velocity;
    sf::CircleShape m_shape;

};



#endif //BALL_H
