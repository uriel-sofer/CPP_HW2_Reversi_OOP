#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"

using namespace std;

/**
 * Represents the actual game. holds players' data, and the board.
 * As for the "Big 5": no need for any, as their going to be only one instance of this class.
 */
class Game {
private:
    Player players[2];
    Board board;
    bool currentPlayer;

    bool checkQuitters() const;
    bool checkPassers() const;

public:
    Game();

    Board getBoard() const;
    void play();

};



#endif //GAME_H
