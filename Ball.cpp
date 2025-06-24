//
// Created by dakus on 05/05/2025.
//

#include "Ball.h"

#include <iostream>
#include <bits/ostream.tcc>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Paddle.h"
#include "Utils.h"

Ball::Ball(float radius, sf::Vector2f position, sf::Color color, float speed, sf::Vector2f velocity) : m_speed(speed), m_velocity(velocity) {
    m_shape.setRadius(radius);
    m_shape.setPosition(position);
    m_shape.setFillColor(color);
    m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
    m_velocity = Utils::normalize(velocity) * speed;
}

Ball::~Ball() {
    std::cout << "Ball delete" << std::endl;
}

void Ball::update(sf::RenderWindow &window, Paddle &playerPaddle, Paddle &botPaddle) {
    move(m_velocity.x, m_velocity.y);
    if (getPosition().y - getRadius() <= 0 || getPosition().y + getRadius() >= window.getSize().y) {
        setVelocity(sf::Vector2f(m_velocity.x, -m_velocity.y));
    }

    if (getGlobalBounds().intersects(playerPaddle.getGlobalBounds()) || getGlobalBounds().intersects(botPaddle.getGlobalBounds())) {
        setVelocity(sf::Vector2f(-m_velocity.x, m_velocity.y));//utiliser abs si problem
    }
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
}

void Ball::move(float dx, float dy) {
    m_shape.move(dx, dy);
}

void Ball::setPosition(sf::Vector2f position) {
    m_shape.setPosition(position);
}

sf::Vector2f Ball::getPosition() const {
    return m_shape.getPosition();
}

float Ball::getRadius() const {
    return m_shape.getRadius();
}

sf::FloatRect Ball::getGlobalBounds() const {
    return m_shape.getGlobalBounds();
}

sf::CircleShape &Ball::getShape() {
    return m_shape;
}

void Ball::setSpeed(float newSpeed) {
    m_speed = newSpeed;
}

float Ball::getSpeed() const {
    return m_speed;
}

void Ball::setVelocity(sf::Vector2f newVelocity) {
    m_velocity = Utils::normalize(newVelocity) * m_speed;
}

sf::Vector2f Ball::getVelocity() const {
    return m_velocity;
}
