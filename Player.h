#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
#include "Board.h"

enum moveType
{
    Quit,
    Pass,
    Index,
    Invalid
};

/**
 * Class representing the player:
 * Color is 'W' or 'B'
 * There is no  use for the Big 5 so the defaults are enough
 */
class Player {
private:
    char const color;
    Board& board;
    bool quitter;

    /**
     * Checks if the string is according to move format (len = 2, letter and number)
     * @param input the player's move string
     * @return true when can be a move
     */
    bool isBoardIndex(const std::string& input);

    /**
     *
     * @param input Parses the move to see what it is from the four types of input
     * @return the move type
     */
    moveType parseMove(const std::string& input);

    std::string promptMove() const;

public:
    Player(char color, Board& board);

    char getColor() const;
    bool isQuitter() const;
    void setQuitter(bool quitter);

    /**
     * Prompts the user/player for a square and tries to take it
     */
    void makeMove();
};

#endif //PLAYER_H
