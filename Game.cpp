#include "Game.h"

#include "StringUtils.h"

Game::Game() : players{Player('b', board), Player('w', board)}
{
    currentPlayer = false;
}

Board Game::getBoard() const
{
    return board;
}

void Game::play() {
    while (!checkQuitters())
    {
        board.display();
        currentPlayer ? players[1].makeMove() : players[0].makeMove();
        currentPlayer = !currentPlayer;
        if (board.isFull()) {
            board.display();

            if (board.isFull())
            {
                const int whiteTokens = board.getWhites();
                const int blackTokens = board.getBlacks();
                board.display();

                if (whiteTokens > blackTokens)
                    cout << "W wins the game" << endl;
                else if (blackTokens > whiteTokens)
                    cout << "B wins the game" << endl;
                else
                    cout << "The game ends in a tie" << endl;

                return;
            }
        }
    }

    if (players[!currentPlayer].isQuitter())
    {
        cout << toUpper(players[!currentPlayer].getColor()) << ": QUIT" << endl;
        cout << toUpper(players[currentPlayer].getColor()) << " wins the game.";
    }

}

bool Game::checkQuitters() const {
    return players[0].isQuitter() or players[1].isQuitter();
}