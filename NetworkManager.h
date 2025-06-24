//
// Created by dakus on 10/05/2025.
//

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include <SFML/Network.hpp>

enum class Roles {
    Server,
    Client
};

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();
    void sendInput();
    void receiveInput();
    void sendState();
    void receiveState();

protected:
    Roles role;
    sf::TcpListener listener;
    sf::TcpSocket client1, client2;
    sf::TcpSocket socket;
};



#endif //NETWORKMANAGER_H
