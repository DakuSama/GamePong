//
// Created by dakus on 08/05/2025.
//

#include "Menu.h"

#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include "GameManager.h"

Menu::Menu(sf::RenderWindow &window, sf::Font &font, GameState &state, MultiState &multiState)
    : m_window(window),
    m_font(font),
    state(state),
    multiState(multiState),
    playButton(nullptr),
    playSoloButton(nullptr),
    playMultiLocalButton(nullptr),
    quitButton(nullptr),
    GameText(nullptr)
{
    playButton = std::make_unique<Button>(sf::Vector2f(100, 50), sf::Vector2f(m_window.getSize().x /2, m_window.getSize().y/ 2 - 50), sf::Color::Green, m_font, "Play");
    playSoloButton = std::make_unique<Button>(sf::Vector2f(100, 50), sf::Vector2f(m_window.getSize().x /2 - 105, m_window.getSize().y/ 2 - 50), sf::Color::Cyan, m_font, "Solo");
    playMultiLocalButton = std::make_unique<Button>(sf::Vector2f(100, 50), sf::Vector2f(m_window.getSize().x /2 + 105, m_window.getSize().y/ 2 - 50), sf::Color::Cyan, m_font, "MultiLocal");
    quitButton = std::make_unique<Button>(sf::Vector2f(100, 50), sf::Vector2f(m_window.getSize().x /2, m_window.getSize().y/ 2 + 50), sf::Color::Red, m_font, "Quit");
    GameText = std::make_unique<Texte>(m_font, sf::Vector2f(m_window.getSize().x / 2, 75), 60, sf::Color::White, "Pong", "Game");
}

Menu::~Menu() {
    std::cout << "Menu delete" << std::endl;
}

void Menu::run() {
    ProcessEvents();
    Render();
}

void Menu::ProcessEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (playButton->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                showMultiChoice = true;
            }
            if (playSoloButton->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && showMultiChoice) {
                multiState = MultiState::Solo;
                state = GameState::Playing;
                showMultiChoice  = false;
            }
            if (playMultiLocalButton->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && showMultiChoice) {
                multiState = MultiState::Local;
                state = GameState::Playing;
                showMultiChoice  = false;
             }
            if (quitButton->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                m_window.close();
            }
        }
    }
}

void Menu::Render() {
    m_window.clear();
    if (!showMultiChoice)
        playButton->draw(m_window);
    if (showMultiChoice) {
        playSoloButton->draw(m_window);
        playMultiLocalButton->draw(m_window);
    }
    quitButton->draw(m_window);
    GameText->draw(m_window);
    m_window.display();
}