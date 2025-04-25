#include "network.h"

#include <fstream>
#include <print>

const std::size_t Network::report_size = 100;

void Network::connect(int port) {
    listener.close();
    socket.disconnect();

    if (listener.listen(port) != sf::Socket::Done) throw std::runtime_error(std::format("failed create the server with port: {}", port));

    listener.accept(socket);
}

void Network::connect(const std::string &ip, int port) {
    listener.close();
    socket.disconnect();

    std::println("Connecting!");

    while (socket.connect(ip, port) != sf::Socket::Done);

    std::println("Connected!");
}

void Network::push(const std::string &str) {
    std::println("send: {}", str);
    char data[report_size] = { 0 };
    int i = 0;
    for (char c : str) data[i++] = c;
    if (socket.send(data, report_size) != sf::Socket::Done) throw std::runtime_error(std::format("failed send the record"));
}

void Network::pull(std::string &str) {
    char data[report_size] = { 0 };
    std::size_t received = 0;
    socket.receive(data, report_size, received);
    if (received == report_size) {
        str.clear();
        for (int i = 0; i < report_size; ++i) str.push_back(data[i]);
    }

    std::println("pull: {}", str);
}
