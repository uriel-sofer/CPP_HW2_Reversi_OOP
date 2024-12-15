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
    bool moveDone = false;

    while (!moveDone) {
        string move = toUpper(promptMove());

        // Parse and handle the move
        switch (parseMove(move)) {
            case Quit:
                quitter = true;
            return;

            case Pass:
                cout << toUpper(color) << ": PASS" << endl << endl;
            return;

            case Index:
                if (this->board.insert(move, color)) {
                    moveDone = true; // Move successfully inserted
                } else {
                    cerr << "Invalid Move; the game awaits a valid move." << endl;
                }
            break;

            default:
                cerr << "Invalid input; please enter a valid move (index, Quit, or Pass)." << endl;
            break;
        }
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
