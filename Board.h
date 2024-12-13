#ifndef GRID_H
#define GRID_H
#include <iostream>

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
    square_state get(int row, char col) const;
    void set(int row, char col, square_state state);

    /**
     * returns true if the move flipped some pieces
     * @param playerMove
     * @param color
     */
    bool isMoveValid(const std::string &playerMove, char color);

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

    /**
     *
     * @param symbol the player's symbol
     * @return corresponding square_state
     */
    square_state convertSymbol(char symbol) const;

    square_state oppositeSymbol(char symbol) const;

public:
    /**
     * Inits an empty board
     */
    Board();

    /**
     * 
     * @param playerMove string repressing the player's move. Can be QUIT, PASS or a place on the board (e.g. E5 or something)
     * @param symbol
     * @return true if the move was valid and was played successfully
     */
    bool insert(const std::string& playerMove, char symbol);

    /**
     * Prints the grid, hopefully with colors
     */
    void display() const;

    bool allWhite() const;

    bool allBlack() const;

    /**
     * Checks if there is another token in any valid direction
     * @return true if there is (que to flip)
     */
    bool checkAlly(std::string& playerMove, char color) const;

    bool checkAllyRow(const std::string& playerMove, char color) const;

    bool checkAllyCol(const std::string& playerMove, char color) const;

    bool checkAllyDiag(const std::string& playerMove, char color)const;

    bool checkIsLonely(const std::string& playerMove, char color) const;

};

#endif //GRID_H
