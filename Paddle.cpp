//
// Created by dakus on 05/05/2025.
//

#include "Paddle.h"

#include <iostream>
#include <bits/ostream.tcc>

Paddle::Paddle(sf::Vector2f size, sf::Vector2f position, sf::Color color, float speed) : speed(speed) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(color);
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);

}

Paddle::~Paddle() {
    std::cout << "Paddle delete" << std::endl;
}

void Paddle::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Paddle::move(float dx,float dy) {
    shape.move(dx,dy);
}

void Paddle::setPosition(sf::Vector2f pos) {
    shape.setPosition(pos);
}

sf::Vector2f Paddle::getPosition()const {
    return shape.getPosition();
}

sf::Vector2f Paddle::getSize()const {
    return shape.getSize();
}

sf::FloatRect Paddle::getGlobalBounds()const {
    return shape.getGlobalBounds();
}

sf::RectangleShape& Paddle::getShape() {
    return shape;
}

void Paddle::setSpeed(float newSpeed) {
    speed = newSpeed;
}


float Paddle::getSpeed()const {
    return speed;
}