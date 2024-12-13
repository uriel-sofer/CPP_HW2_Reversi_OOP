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
    cout << toUpper(color) << ":" << endl;
    cin >> input;
    return input;
}

void Player::makeMove()
{
    string move = toUpper(promptMove());
    bool moveDone;

    switch (parseMove(move))
    {
        case Quit:
            quitter = true;
            return;


        case Pass:
            cout << toUpper(color) << ": PASS" << endl;
            return;

        case Index:
            moveDone = this->board.insert(toUpper(move), color);
            while (not moveDone)
            {
                cerr << "Invalid Move; the game awaits a valid move." << endl;
                move = toUpper(promptMove());
                moveDone = this->board.insert(toUpper(move), color);
            }
            return;

        default:
            while (parseMove(move) == Invalid)
            {
                cerr << "Invalid Move; the game awaits a valid move." << endl;
            }
            this->board.insert(toUpper(promptMove()), color);

    }
}

moveType Player::parseMove(const string& input)
{
    if (input == "QUIT") return Quit;
    if (input == "PASS") return Pass;
    if (isBoardIndex(input)) return Index;
    return Invalid;
}

bool Player::isBoardIndex(const string& input)
{
    const string move = toUpper(input);
    if (move.length() == 2
        and (move[0] >= 'A' or move [0] <= 'A' + ROWS - 1)
        and (move[1] >= 1 or move [1] <= COLUMNS))
    {
        return true;
    }
    return false;
}
