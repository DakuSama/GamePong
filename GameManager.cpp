//
// Created by dakus on 05/05/2025.

#include "GameManager.h"

#include <complex>
#include <iostream>
#include <SFML/Window/Event.hpp>

/**
 * @brief Constructs a new GameManager object and initializes all required components for the game.
 *
 * This constructor initializes the game window, player paddle, bot paddle, and ball with predefined
 * dimensions, positions, velocities, and colors. It also loads the necessary font for text display.
 * Additionally, it sets up the game state, score tracking variables, and UI elements such as pause
 * text, win text, and score display.
 *
 * @return A new instance of the GameManager class with all entities and resources initialized.
 *         If the required font file is not found, an error message is printed.
 */
GameManager::GameManager()
    : m_window(sf::VideoMode(1920/2, 1080/2), "Pong", sf::Style::None),
    m_playerPaddle(sf::Vector2f(m_window.getSize().x /40, m_window.getSize().y / 4), sf::Vector2f(50,m_window.getSize().y /2), sf::Color::White),
    m_botPaddle(sf::Vector2f(m_window.getSize().x /40, m_window.getSize().y / 4), sf::Vector2f(m_window.getSize().x - 50,m_window.getSize().y /2), sf::Color::Red),
    m_ball(std::sqrt(m_window.getSize().x * m_window.getSize().x + m_window.getSize().y * m_window.getSize().y) / 75, sf::Vector2f(m_window.getSize().x /2, m_window.getSize().y / 2), sf::Color::White, 10, sf::Vector2f(-4,4)),
    m_multiPlayer(MultiState::Solo),
    m_scorePlayer(0),
    m_scoreBot(0),
    m_maxScore(1),
    state(GameState::InMenu),
    pauseText(nullptr),
    winText(nullptr),
    scoreText(nullptr),
    restarButton(nullptr),
    MenuButton(nullptr),
    QuitButton(nullptr),
    menu(nullptr)
{
    m_window.setFramerateLimit(60);
    std::cout << "Game create " << std::endl;
    if (!m_font.loadFromFile("assets/arial.ttf")) {
        std::cout << "Font load error" << std::endl;
    }
    pauseText = std::make_unique<Texte>(m_font, sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2), 50, sf::Color::Red, "Pause", "pause");
    winText = std::make_unique<Texte>(m_font, sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2 -200), 50, sf::Color::Green, "win", "win");
    scoreText = std::make_unique<Texte>(m_font, sf::Vector2f(m_window.getSize().x / 2, 50), 50, sf::Color::White, "0:0", "score");
    restarButton = std::make_unique<Button>(sf::Vector2f(m_window.getSize().x /10, m_window.getSize().y /10), sf::Vector2f(m_window.getSize().x/ 2, m_window.getSize().y/ 2 -70), sf::Color::Yellow, m_font, "Restart", sf::Color::Black);
    MenuButton = std::make_unique<Button>(sf::Vector2f(m_window.getSize().x /10, m_window.getSize().y /10), sf::Vector2f(m_window.getSize().x/ 2, m_window.getSize().y/ 2), sf::Color::Magenta, m_font, "Go to Menu");
    QuitButton = std::make_unique<Button>(sf::Vector2f(m_window.getSize().x /10, m_window.getSize().y /10), sf::Vector2f(m_window.getSize().x/ 2, m_window.getSize().y/ 2 +70), sf::Color::Red, m_font, "Quit");
    menu = std::make_unique<Menu>(m_window, m_font, state, m_multiPlayer);
}

GameManager::~GameManager() {
    std::cout << "Game delete" << std::endl;
}

void GameManager::run() {
    while (m_window.isOpen()) {
        if (state == GameState::Playing || state == GameState::IsPaused || state == GameState::GameOver) {
            ProcessEvents();
            Update();
            Render();
        }
        else if (state == GameState::InMenu) {
            menu->run();
        }

    }
}

void GameManager::ProcessEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            if (state == GameState::Playing)
                state = GameState::IsPaused;
            else if (state == GameState::IsPaused)
                state = GameState::Playing;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && state == GameState::GameOver) {
            Reset();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && state == GameState::GameOver) {
            sf::Vector2f mousePos(m_window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y}));
            if (restarButton->getGlobalBounds().contains(mousePos)) {
                Reset();
            }
            if (MenuButton->getGlobalBounds().contains(mousePos)) {
                Reset();
                state = GameState::InMenu;
            }
            if (QuitButton->getGlobalBounds().contains(mousePos)) {
                m_window.close();
            }
        }
    }
}

void GameManager::Update() {
    if (state == GameState::Playing) {
        HandlePlayerInput();
        m_ball.update(m_window, m_playerPaddle, m_botPaddle);
        HandleScore();
    }
}

void GameManager::HandlePlayerInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && m_playerPaddle.getPosition().y > m_playerPaddle.getSize().y / 2 + 10) {
        m_playerPaddle.move(0, -m_playerPaddle.getSpeed());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_playerPaddle.getPosition().y < m_window.getSize().y - m_playerPaddle.getSize().y / 2 - 10) {
        m_playerPaddle.move(0, m_playerPaddle.getSpeed());
    }
    if (m_multiPlayer == MultiState::Local) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_botPaddle.getPosition().y > m_botPaddle.getSize().y / 2 + 10) {
            m_botPaddle.move(0, -m_botPaddle.getSpeed());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_botPaddle.getPosition().y < m_window.getSize().y - m_botPaddle.getSize().y / 2 - 10) {
            m_botPaddle.move(0, m_botPaddle.getSpeed());
        }
    }
    else if (m_multiPlayer == MultiState::Solo){
        AI();
    }
}

void GameManager::AI() {
    if (m_ball.getPosition().y + m_ball.getRadius() > m_botPaddle.getPosition().y + m_botPaddle.getSize().y / 2) {
        if (m_botPaddle.getPosition().y + m_botPaddle.getSize().y / 2 < m_window.getSize().y) {
            m_botPaddle.move(0,m_playerPaddle.getSpeed());
        }
    }
    if (m_ball.getPosition().y + m_ball.getRadius() < m_botPaddle.getPosition().y + m_botPaddle.getSize().y / 2) {
        if (m_botPaddle.getPosition().y - m_botPaddle.getSize().y / 2 > 0) {
            m_botPaddle.move(0,-m_playerPaddle.getSpeed());
        }
    }
}

void GameManager::HandleScore() {
    if (m_ball.getPosition().x < 0) {
        m_scoreBot ++;
        std::cout <<"Score Bot : "<<m_scoreBot<<std::endl;
        scoreText->setString(std::to_string(m_scorePlayer) + ":" + std::to_string(m_scoreBot));
        m_ball.setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2));
        m_ball.setVelocity(sf::Vector2f(-m_ball.getVelocity().x, m_ball.getVelocity().y));

        if (m_scoreBot >= m_maxScore) {
            state = GameState::GameOver;
            winText->setString("Bot WINNER");
        }
    }
    if (m_ball.getPosition().x > m_window.getSize().x) {
        m_scorePlayer ++;
        std::cout <<"Score Player : "<<m_scorePlayer<<std::endl;
        scoreText->setString(std::to_string(m_scorePlayer) + ":" + std::to_string(m_scoreBot));
        m_ball.setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2));
        m_ball.setVelocity(sf::Vector2f(-m_ball.getVelocity().x, m_ball.getVelocity().y));

        if (m_scorePlayer >= m_maxScore) {
            state = GameState::GameOver;
            winText->setString("Player WINNER");
        }
    }
}


void GameManager::Render() {
    m_window.clear();
    m_ball.draw(m_window);
    m_botPaddle.draw(m_window);
    m_playerPaddle.draw(m_window);
    scoreText->draw(m_window);
    if (state == GameState::IsPaused) {
        pauseText->draw(m_window);
    }
    if (state == GameState::GameOver) {
        winText->draw(m_window);
        restarButton->draw(m_window);
        MenuButton->draw(m_window);
        QuitButton->draw(m_window);
    }
    m_window.display();
}

void GameManager::Reset() {
    m_scorePlayer = 0;
    m_scoreBot = 0;
    scoreText->setString("0:0");
    state = GameState::Playing;
    m_ball.setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2));
    m_playerPaddle.setPosition(sf::Vector2f(50, m_window.getSize().y / 2));
    m_botPaddle.setPosition(sf::Vector2f(m_window.getSize().x - 50, m_window.getSize().y / 2));
}
