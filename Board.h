#ifndef GRID_H
#define GRID_H

using namespace std;

enum square_state
{
    Empty,
    Black,
    White,
    err // Out of bounds
};

/**
 * represents the game board,
 * has an array of square_states, which can only hold three values
 * Default d'tor is enough
 * Default copy c'tor is enough (shallow pointer copy)
 * The other two are not relevant
 */

constexpr int ROWS = 8;
constexpr int COLUMNS = 8;

class Board {
private:
    square_state grid[ROWS][COLUMNS]{};
    square_state get(char row, char col) const;
    void set(int row, char col, square_state state);

    /**
     * Attempts to flip the piece at (row, col)
     * @param row row (staring from 1 to 8)
     * @param col col (starting from A to H)
     */
    bool flip(int row, char col);

    /**
     * checks if index is on the grid
     * @param row row (staring from 1 to 8)
     * @param col col (starting from A to H)
     * @return true if in bounds, false if out of bounds
     */
    bool check(int row, int col) const;

    /**
     * returns what char to print for each of the square states
     * @param state state
     */
    char printSingleState(square_state state) const;

    /**
     * Converts col to numeric value
     * @param col col (starting from A to H)
     * @return 1-8
     */
    int convertCol(char col) const;


public:
    /**
     * Inits an empty board
     */
    Board();

    /**
     * 
     * @param playerMove string represting the player's move. Can be QUIT, PASS or a place on the borad (e.g E5 or something)
     * @return true if the move was valid and was played successfully
     */
    bool insert(string& playerMove);

    /**
     * Prints the grid, hopefully with colors
     */
    void display() const;
};



#endif //GRID_H
