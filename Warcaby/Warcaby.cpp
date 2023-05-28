#include "checkers.h"

CheckersGame::CheckersGame() {
    currentTurn = RED_TURN;
    initializeBoard();
}

void CheckersGame::initializeBoard() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if ((row + col) % 2 == 0) {
                if (row < 3)
                    board[row][col] = BLACK;
                else if (row > 4)
                    board[row][col] = RED;
                else
                    board[row][col] = EMPTY;
            }
            else {
                board[row][col] = EMPTY;
            }
        }
    }
}

void CheckersGame::printBoard() {
    std::cout << "   ";
    for (int col = 0; col < BOARD_SIZE; col++)
        std::cout << col << " ";
    std::cout << std::endl;

    for (int row = 0; row < BOARD_SIZE; row++) {
        std::cout << row << "  ";
        for (int col = 0; col < BOARD_SIZE; col++) {
            switch (board[row][col]) {
            case EMPTY:
                std::cout << ". ";
                break;
            case RED:
                std::cout << "R ";
                break;
            case BLACK:
                std::cout << "B ";
                break;
            }
        }
        std::cout << std::endl;
    }
}

bool CheckersGame::isValidMove(const Move& move) {
    int fromRow = move.fromRow;
    int fromCol = move.fromCol;
    int toRow = move.toRow;
    int toCol = move.toCol;

    // czy pole docelowe jest w granicach planszy
    if (toRow < 0 || toRow >= BOARD_SIZE || toCol < 0 || toCol >= BOARD_SIZE)
        return false;

    // czy pole docelowe jest puste
    if (board[toRow][toCol] != EMPTY)
        return false;

    // czy pole początkowe zawiera pionek gracza wykonującego ruch
    Piece currentPiece = board[fromRow][fromCol];
    if (currentPiece == EMPTY)
        return false;

    // czy ruch jest wykonywany przez odpowiedniego gracza
    if (currentPiece == RED && currentTurn == BLACK_TURN)
        return false;
    if (currentPiece == BLACK && currentTurn == RED_TURN)
        return false;

    // czy ruch czerwonych pionków jest w poprawnym kierunku
    if (currentPiece == RED && toRow >= fromRow)
        return false;
    // czy ruch czarnych pionków jest w poprawnym kierunku
    if (currentPiece == BLACK && toRow <= fromRow)
        return false;

    int rowDiff = abs(fromRow - toRow);
    int colDiff = abs(fromCol - toCol);

    // czy ruch jest na ukos
    if (rowDiff != colDiff)
        return false;

    // Ruch o jedno pole == poprawny
    if (rowDiff == 1)
        return true;

    // czy skok jest możliwy - pole pośrednie musi zawierać pionek przeciwnika
    int jumpRow = (fromRow + toRow) / 2;
    int jumpCol = (fromCol + toCol) / 2;
    if (board[jumpRow][jumpCol] == EMPTY)
        return false;

    Piece opponentPiece = (currentPiece == RED) ? BLACK : RED;
    // czy pole pośrednie zawiera pionek przeciwnika
    if (board[jumpRow][jumpCol] != opponentPiece)
        return false;

    return true;
}

bool CheckersGame::isGameOver() {
    int redPieces = 0;
    int blackPieces = 0;

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == RED)
                redPieces++;
            else if (board[row][col] == BLACK)
                blackPieces++;
        }
    }

    return redPieces == 0 || blackPieces == 0;
}

void CheckersGame::makeMove(const Move& move) {
    int fromRow = move.fromRow;
    int fromCol = move.fromCol;
    int toRow = move.toRow;
    int toCol = move.toCol;

    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = EMPTY;

    int jumpRow = (fromRow + toRow) / 2;
    int jumpCol = (fromCol + toCol) / 2;
    if (abs(fromRow - toRow) == 2 && abs(fromCol - toCol) == 2) {
        board[jumpRow][jumpCol] = EMPTY;
    }

    currentTurn = (currentTurn == RED_TURN) ? BLACK_TURN : RED_TURN;
}
