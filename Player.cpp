#include "Player.h"
#include "Board.h"
#include "StringUtils.h"

using namespace std;

Player::Player(const char color, Board& board) : color(color), board(board)
{
    this->board = board;
    quitter = false;
}

char Player::getColor() const
{
    return this->color;
}

bool Player::isQuitter() const {
    return this->quitter;
}

void Player::setQuitter(const bool quitter)
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
    const string move = toUpper(promptMove());

    if (move == "QUIT")
    {
        quitter = true;
        return;
    }

    if (move == "PASS")
    {
        return;
    }
    bool madeMove = this->board.insert(toUpper(move), color);;
    while (!madeMove)
    {
        cerr << "Please enter a valid move: " << endl;
        madeMove = this->board.insert(toUpper(promptMove()), color);;
    }
}

