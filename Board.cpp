#include <iostream>
#include "Board.h"

#include "StringUtils.h"


using namespace std;

Board::Board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            grid[i][j] = Empty;
        }
    }

    grid[3][3] = Black;
    grid[3][4] = White;
    grid[4][3] = White;
    grid[4][4] = Black;
}


square_state Board::get(const int row, const char col) const
{
    const int numCol = convertCol(col);
    if (!check(row,numCol))
    {
        return err;
    }
    return grid[row - 1][numCol - 1];
}

void Board::set(const int row, const char col, char symbol)
{
    const int numCol = convertCol(col);
    if (check(row, col) && symbol != err)
    {
        if(toUpper(symbol) == 'W')
            grid[row - 1][numCol - 1] = White;
        else if(toUpper(symbol) == 'B')
            grid[row - 1][numCol - 1] = Black;
    }
}

bool Board::isMoveValid(const string &playerMove, const char color) const
{
    if (!check(playerMove))
    {
        return false;
    }

    const int row = playerMove[1] - '0';
    const int col = convertCol(playerMove[0]);

    return canFlipInDirection(row, col, -1, 0, color) || // Up
           canFlipInDirection(row, col, 1, 0, color) ||  // Down
           canFlipInDirection(row, col, 0, -1, color) || // Left
           canFlipInDirection(row, col, 0, 1, color) ||  // Right
           canFlipInDirection(row, col, -1, -1, color) || // Up-Left
           canFlipInDirection(row, col, -1, 1, color) ||  // Up-Right
           canFlipInDirection(row, col, 1, -1, color) ||  // Down-Left
           canFlipInDirection(row, col, 1, 1, color);     // Down-Right
}

bool Board::insert(const string& playerMove, const char symbol)
{
    if (!isMoveValid(playerMove, symbol))
        {
            cerr << "Invalid move" << endl;
            return false;
        }

    const int row = playerMove[1] - '0';
    const int col = convertCol(playerMove[0]);
    grid[row - 1][col - 1] = convertSymbol(symbol);

    flipTokens(row, col, symbol);
    return true;
}

void Board::flipTokens(const int row, const int col, const char symbol)
{
    for (int dRow = -1; dRow <= 1; dRow++) {
        for (int dCol = -1; dCol <= 1; dCol++) {
            if (dRow == 0 && dCol == 0) continue; // Skip the origin cell

            int currentRow = row + dRow;
            int currentCol = col + dCol;

            // Check if tokens can be flipped in this direction
            if (canFlip(currentRow, currentCol, dRow, dCol, symbol)) {
                // Flip tokens in this direction
                while (grid[currentRow - 1][currentCol - 1] == oppositeSymbol(symbol)) {
                    grid[currentRow - 1][currentCol - 1] = convertSymbol(symbol);
                    currentRow += dRow;
                    currentCol += dCol;
                }
            }
        }
    }
}

bool Board::canFlip(int row, int col, const int dRow, const int dCol, const char symbol) const
{
    bool foundOpponent = false;

    while (check(row, col)) {
        if (grid[row - 1][col - 1] == Empty) return false;
        if (grid[row - 1][col - 1] == convertSymbol(symbol)) return foundOpponent;

        foundOpponent = true; // Found at least one opponent token
        row += dRow;
        col += dCol;
    }

    return false; // Out of bounds
}

bool Board::canFlipInDirection(const int startRow, const int startCol, const int dRow, const int dCol, const char color) const {
    int currentRow = startRow + dRow;
    int currentCol = startCol + dCol;

    bool foundOpponent = false;

    while (check(currentRow, currentCol)) {
        const square_state currentSquare = grid[currentRow - 1][currentCol - 1];

        if (currentSquare == Empty) {
            return false;
        }
        if (currentSquare == convertSymbol(color)) {
            return foundOpponent;
        }

        foundOpponent = true;
        currentRow += dRow;
        currentCol += dCol;
    }

    return false;
}

void Board::display() const
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            cout << printSingleState(grid[i][j]) << " ";
        }
        //cout << i + 1<< endl << endl; Add rows numbers
    }
    // Add columns letters
    // for (int i = 0; i < COLUMNS; i++)
    // {
    //     cout << (char)('A' + i) << " ";
    // }
    // cout << endl << endl;
}

bool Board::check(const string& playerMove) const
{
    const int row = playerMove[1] - '0';
    const int col = convertCol(playerMove[0]);

    return check(row, col);
}

bool Board::check(const int row, const int col) const
{
    return row >= 1 && row <= ROWS && col >= 1 && col <= COLUMNS;
}

char Board::printSingleState(square_state state) const
{
    switch (state)
    {
        case Black: return 'B';
        case White: return 'W';
        default: return 'O';
    }
}


int Board::convertCol(char col) const
{
    return col - 'A' + 1;
}

square_state Board::convertSymbol(const char symbol) const {
    switch (symbol) {
        case 'b': return Black;
        case 'w': return White;
        default: return Empty;
    }
}

square_state Board::oppositeSymbol(const char symbol) const {
    switch (toUpper(symbol)) {
        case 'B': return White;
        case 'W': return Black;
        default: return Empty;
    }
}


bool Board::allWhite() const {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (grid[i][j] != White) {
                return false;
            }
        }
    }
    return true;
}

bool Board::allBlack() const {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (grid[i][j] != Black) {
                return false;
            }
        }
    }
    return true;
}


bool Board::checkAllyRow(const std::string &playerMove, const char color) const {
    const int col = convertCol(playerMove[0]);
    const int row = playerMove[1] - '0';

    int enemyTokens = 0;
    // Check right
    for (int i = col + 1; i < ROWS; i++) {
        if (grid[row][i] == oppositeSymbol(color)) {
            enemyTokens++;
        }
        else if (grid[row][i] == Empty) {
            return false;
        }
    }

    enemyTokens = 0;
    // Check left
    for (int i = col - 1; i >= 0; i--) {
        if (grid[row][i] == oppositeSymbol(color)) {
            enemyTokens++;
        }
        else if (grid[row][i] == Empty) {
            return false;
        }
    }

    return true;
}

bool Board::checkAllyCol(const std::string &playerMove, const char color) const {
    const int col = convertCol(playerMove[0]);
    const int row = playerMove[1] - '0';

    int enemyTokens = 0;
    for (int i = row + 1; i < COLUMNS; i++) {
        if (grid[i][col] == oppositeSymbol(color)) {
            enemyTokens++;
        }
        else if (grid[i][col] == Empty) {
            return false;
        }
    }

    enemyTokens = 0;
    for (int i = row - 1; i >= 0; i--) {
        if (grid[i][col] == oppositeSymbol(color)) {
            enemyTokens++;
        }
        else if (grid[i][col] == Empty) {
            return false;
        }
    }

    return true;
}
/*
bool Board::checkAllyDiag(const std::string &playerMove, char color) const {

}*/


