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

class Board
{
private:
    int whites;
    int blacks;
    square_state grid[ROWS][COLUMNS]{};

    square_state get(int row, char col) const;

    void set(int row, char col, char symbol);

    /**
     * returns true if the move flipped some pieces
     * @param playerMove
     * @param color
     */
    bool isMoveValid(const std::string& playerMove, char color) const;

    /**
     * Checks all 8 possible directions for valid flips.
     * @param color The symbol of the current player (e.g., 'W' or 'B').
     * @param row The row index of the move.
     * @param col The column index of the move.
     * @return True if a flip is possible in any direction, false otherwise.
     */
    bool canFlipInAnyDirection(char color, int row, int col) const;

    /**
     * checks if index is on the grid
     * @param row row (staring from 1 to ROWS)
     * @param col col (starting from A to COLLUMNS)
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
     * @param symbol the player's symbol
     * @return corresponding square_state
     */
    square_state convertSymbol(char symbol) const;

    /**
     * @param symbol the symbol to get the opposite of
     * @return opposite of the symbol
     */
    square_state oppositeSymbol(char symbol) const;

    /**
     * Flips tokens in all valid directions based on the current move.
     * @param row The row index of the move.
     * @param col The column index of the move.
     * @param symbol The symbol of the current player (e.g., 'W' or 'B').
     */
    void flipTokens(int row, int col, char symbol);

    /**
     * Checks if tokens can be flipped in a specific direction.
     * @param startRow The starting row index.
     * @param startCol The starting column index.
     * @param dRow The row direction (e.g., -1 for up, 1 for down).
     * @param dCol The column direction (e.g., -1 for left, 1 for right).
     * @param color The symbol of the current player (e.g., 'W' or 'B').
     * @return True if a flip is possible in the specified direction, false otherwise.
     */
    bool canFlipInDirection(int startRow, int startCol, int dRow, int dCol, char color) const;

    /**
     * Flips tokens in a specific direction.
     * @param startRow The starting row index.
     * @param startCol The starting column index.
     * @param dRow The row direction (e.g., -1 for up, 1 for down).
     * @param dCol The column direction (e.g., -1 for left, 1 for right).
     * @param symbol The symbol of the current player (e.g., 'W' or 'B').
     */
    void flipInDirection(int startRow, int startCol, int dRow, int dCol, char symbol);

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

    int getWhites() const;

    int getBlacks() const;

    /**
     * Prints the grid
     */
    void display() const;

    /**
     *
     * @param playerMove string representing the player's move
     * @return true if in bounds
     */
    bool check(const std::string& playerMove) const;

    bool isFull() const;
};

#endif //GRID_H