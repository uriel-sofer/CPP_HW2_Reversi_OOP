#include <iostream>
#include "Board.h"

#include "StringUtils.h"


using namespace std;

Board::Board()
{
    whites = 2;
    blacks = 2;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            grid[i][j] = Empty;
        }
    }

    grid[3][3] = White;
    grid[3][4] = Black;
    grid[4][3] = Black;
    grid[4][4] = White;
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

int Board::getBlacks() const
{
    return blacks;
}

int Board::getWhites() const
{
    return whites;
}

bool Board::isMoveValid(const string &playerMove, const char color) const
{
    if (!check(playerMove))
    {
        return false;
    }

    const int row = playerMove[1] - '0';
    const int col = convertCol(playerMove[0]);

    return checkFlipDirections(color, row, col);
}

bool Board::checkFlipDirections(const char color, const int row, const int col) const
{
    return canFlipInDirection(row, col, -1, 0, color) or // Up
        canFlipInDirection(row, col, 1, 0, color) or // Down
        canFlipInDirection(row, col, 0, -1, color) or // Left
        canFlipInDirection(row, col, 0, 1, color) or // Right
        canFlipInDirection(row, col, -1, -1, color) or // Up-Left
        canFlipInDirection(row, col, -1, 1, color) or // Up-Right
        canFlipInDirection(row, col, 1, -1, color) or // Down-Left
        canFlipInDirection(row, col, 1, 1, color); // Down-Right
}

bool Board::insert(const string& playerMove, const char symbol)
{
    if (!isMoveValid(playerMove, symbol))
        {
            return false;
        }

    const int row = playerMove[1] - '0';
    const int col = convertCol(playerMove[0]);
    grid[row - 1][col - 1] = convertSymbol(symbol);

    if (toUpper(symbol) == 'W')
        whites++;
    else if (toUpper(symbol) == 'B')
        blacks++;

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
        //cout << endl << endl;
        cout << i + 1<< endl << endl; //Add rows numbers
    }
    //Add columns letters
    for (int i = 0; i < COLUMNS; i++)
    {
        cout << (char)('A' + i) << " ";
    }
    cout << endl << endl;
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


bool Board::isFull() const
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (grid[i][j] == Empty)
            {
                return false;
            }
        }
    }
    return true;
}





