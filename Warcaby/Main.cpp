#include "checkers.h"

int main() {
    CheckersGame game;

    while (!game.isGameOver()) {
        game.printBoard();

        int fromRow, fromCol, toRow, toCol;
        std::cout << "Enter move (from-Row from-Col to-Row to-Col): ";
        std::cin >> fromRow >> fromCol >> toRow >> toCol;

        Move move = { fromRow, fromCol, toRow, toCol };

        if (game.isValidMove(move)) {
            game.makeMove(move);
        }
        else {
            std::cout << "Invalid move! Try again." << std::endl;
        }
    }

    std::cout << "Game over!" << std::endl;

    return 0;
}
