#pragma once

#include "board.h"
#include "piece.h"
#include "network.h"

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>

class ChessGame : public sf::Drawable {
private:
    Board board;
    std::array<Piece, 16> whitePieces;
    std::array<Piece, 16> blackPieces;
    Piece *selectedPiece;
    std::vector<sf::RectangleShape> possibleMovesSquares;
    std::string lastMove;

    sf::RectangleShape infoRestart;

    sf::Font font;
    sf::Text textRestart;
    sf::Text textTurn;
    sf::Text textSituation;
    sf::Text textLastMove;

    bool selected;
    bool playerTurn;
    bool playerTurnCheck;
    bool mate;
    int turn;
    bool is_white;

    Network network;
    std::string push_str;
    std::string pull_str;

    void connect();

    void createMovesSquares();

    void calcPossibleMoves();
    void calcKingMoves(Piece *tmpPiece);
    void calcQueenMoves(Piece *tmpPiece);
    void calcRookMoves(Piece *tmpPiece);
    void calcBishopMoves(Piece *tmpPiece);
    void calcKnightMoves(Piece *tmpPiece);
    void calcPawnMoves(Piece *tmpPiece);
    void calcCastling(Piece *tmpPiece);

    void eraseMoves(Piece *tmpPiece);
    void checkMate();
    void updateInfo();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    ChessGame(sf::Color bordCol1, sf::Color bordCol2);

    inline bool getSelected() { return selected; }

    inline bool getMate() { return mate; }

    void selectPiece(int pos);
    void moveSelected(int pos);
    void restart();

    void update();
};
