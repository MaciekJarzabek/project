#pragma once

#include <iostream>

const int BOARD_SIZE = 8;

enum Piece { EMPTY, RED, BLACK };
enum Turn { RED_TURN, BLACK_TURN };

struct Move {
    int fromRow, fromCol;
    int toRow, toCol;
};

class CheckersGame {
private:
    Piece board[BOARD_SIZE][BOARD_SIZE];
    Turn currentTurn;

public:
    CheckersGame();

    void initializeBoard();

    void printBoard();

    bool isValidMove(const Move& move);

    bool isGameOver();

    void makeMove(const Move& move);
};

