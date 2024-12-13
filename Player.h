#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>

#include "Board.h"

/**
 * Class representing the player:
 * Color is 'W' or 'B'
 */
class Player {
    private:
    char const color;
    Board& board;
    bool quitter;

private:
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
