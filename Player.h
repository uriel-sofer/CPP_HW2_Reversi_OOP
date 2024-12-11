#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>

#include "Board.h"

class Player {
    private:
    char const color;
    Board& board;
    bool quitter;


    public:
    Player(char color, Board& board);

    char getColor();

    void setQuitter(bool quitter);

    /**
     * Prompts the user/player for a square and tries to take it
     */
    void makeMove();

    std::string promptMove() const;
};



#endif //PLAYER_H
