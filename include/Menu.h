//
// Created by dakus on 08/05/2025.
//

#ifndef MENU_H
#define MENU_H
#include <memory>
#include "GameState.h"
#include "MultiState.h"
#include "Button.h"


class Menu {
public:
    Menu(sf::RenderWindow &window, sf::Font &font, GameState &state, MultiState &multiState);
    ~Menu();
    void run();

protected:
    void ProcessEvents();
    void Render();

    sf::RenderWindow &m_window;
    sf::Font &m_font;
    GameState &state;
    MultiState &multiState;
    std::unique_ptr<Button> playButton;
    std::unique_ptr<Button> playSoloButton;
    std::unique_ptr<Button> playMultiLocalButton;
    std::unique_ptr<Button> quitButton;
    std::unique_ptr<Texte> GameText;
    bool showMultiChoice = false;
};



#endif //MENU_H
