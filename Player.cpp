#include "Player.h"
#include "Board.h"


using namespace std;

Player::Player(char color, Board& board): board(board), color(color)
{
    this->board = board;
    quitter = false;
}

char Player::getColor()
{
    return this->color;
}

void Player::setQuitter(bool quitter)
{
    this->quitter = quitter;
}


std::string Player::promptMove() const
{
    string input;
    cout << color << ":" << endl;
    cin >> input;
    return input;
}

void Player::makeMove()
{
    string move = promptMove();
    if (move == "QUIT")
    {
        quitter = true;
        return;
    }

    if (move == "PASS")
    {
        return;
    }

    this->board.insert(move);

}

