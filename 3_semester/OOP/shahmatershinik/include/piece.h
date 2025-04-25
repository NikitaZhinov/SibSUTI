#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "pieceTextures.h"

class Piece : public sf::Drawable {
public:
    Piece(char type = 'P', bool player = true, int pos = -1, bool moved = false)
        : m_type(type), m_player(player), m_position(-1), m_moved(true), enPassant(-1) {}

    void setPiece(char type, bool player, int pos, bool moved = false);

    inline void setType(char ch) {
        m_type = ch;
        setTexture();
    }

    inline char getType() { return m_type; }

    inline void setPlayer(bool bl) {
        m_player = bl;
        setTexture();
    }

    inline bool getPlayer() { return m_player; }

    inline void setPosition(int pos) {
        m_position = pos;
        move();
    }

    inline int getPosition() { return m_position; }

    inline void setMoved(bool moved) { m_moved = moved; }

    inline bool getMoved() { return m_moved; }

    inline void setEnPassant(int x) { enPassant = x; }

    inline int getEnPassant() { return enPassant; }

    inline std::vector<int> &getPossibleMoves() { return possibleMoves; }

    inline std::vector<int> &getDangerMoves() { return dangerMoves; }

    std::string toString();

private:
    sf::Sprite m_sprite;
    std::vector<int> possibleMoves;
    std::vector<int> dangerMoves;

    char m_type;
    bool m_player;
    int m_position;
    int enPassant;
    bool m_moved;

    void setTexture();
    void move();

    inline virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_sprite);
    }
};
