//
// Created by dakus on 05/05/2025.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameState.h"
#include "MultiState.h"
#include "Ball.h"
#include "Button.h"
#include "Menu.h"
#include "NetworkManager.h"
#include "Paddle.h"
#include "Texte.h"



class GameManager {
public:
    GameManager();
    ~GameManager();
    void run();

protected:
    void ProcessEvents();
    void Update();
    void Render();
    void HandlePlayerInput();
    void AI();
    void HandleScore();
    void Reset();

    Roles role;
    //NetworkManager net;
    sf::RenderWindow m_window;
    Paddle m_playerPaddle;
    Paddle m_botPaddle;
    Ball m_ball;
    MultiState m_multiPlayer;
    int m_scorePlayer;
    int m_scoreBot;
    int m_maxScore;
    GameState state;
    sf::Font m_font;
    std::unique_ptr<Texte> pauseText;
    std::unique_ptr<Texte> scoreText;
    std::unique_ptr<Texte> winText;
    std::unique_ptr<Button> restarButton;
    std::unique_ptr<Button> MenuButton;
    std::unique_ptr<Button> QuitButton;
    std::unique_ptr<Menu> menu;
};



#endif //GAMEMANAGER_H
