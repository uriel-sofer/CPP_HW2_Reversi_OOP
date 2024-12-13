#include "Game.h"

Game::Game() : players{Player('b', board), Player('w', board)} {
    currentPlayer = false;
}

void Game::play() {
    while (!checkQuitters()) {
        board.display();
        currentPlayer ? players[0].makeMove() : players[1].makeMove();
        currentPlayer = !currentPlayer;
        if (checkWinner()) {
            board.display();
            cout << "Player " << currentPlayer << " wins!" << endl;
        }
    }
}

bool Game::checkQuitters() const {
    return players[0].isQuitter() && players[1].isQuitter();
}

bool Game::checkWinner() const {
    if (board.allBlack())
        return true;

    if (board.allWhite())
        return true;

    return false;
}
