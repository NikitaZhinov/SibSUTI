#pragma once

#include <SFML/Network.hpp>

#include <string>

class Network {
private:
    sf::TcpListener listener;
    sf::TcpSocket socket;

    static const std::size_t report_size;

public:
    void connect(int port);
    void connect(const std::string &ip, int port);
    void push(const std::string &str);
    void pull(std::string &str);
};
