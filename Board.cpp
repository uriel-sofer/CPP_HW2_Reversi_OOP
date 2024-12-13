#include <iostream>
#include "Board.h"


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
    if (check(row,numCol))
    {
        return err;
    }
    return grid[row - 1][numCol - 1];
}

void Board::set(const int row, const char col, const square_state state)
{
    int numCol = convertCol(col);
    if (check(row, col) && state != err)
    {
        grid[row - 1][numCol - 1] = state;
    }
}

bool Board::isMoveValid(const string &playerMove, char color)
{
    int numCol = convertCol(playerMove[0]);
    int row = playerMove[1] - '0';
    if (checkAllyRow(playerMove, color) && checkAllyCol(playerMove, color))
        return true;

    return false;
}

bool Board::insert(const string& playerMove, const char symbol)
{
    if (!isMoveValid(playerMove, convertSymbol(symbol))) return false;

    const int row = playerMove[1] - '0';

    if (check(row, playerMove[0])) {
        set(row, playerMove[0], convertSymbol(symbol));
        return true;
    }

}

void Board::display() const
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << printSingleState(grid[i][j]) << " ";
        }
        cout << endl << endl;
    }
}

bool Board::check(const int row, const int col) const
{
    return row >= 1 && row <= 8 && col >= 'A' && col <= 'H';
}

char Board::printSingleState(square_state state) const
{
    switch (state)
    {
        case Black:
            return 'B';

        case White:
            return 'W';

        default:
            return 'O';
    }
}


int Board::convertCol(char col) const
{
    return col - 'A' + 1;
}

square_state Board::convertSymbol(const char symbol) const {
    switch (symbol) {
        case 'b':
            return Black;
        case 'w':
            return White;

        default:
            return Empty;
    }
}

square_state Board::oppositeSymbol(const char symbol) const {
    switch (convertSymbol(symbol)) {

        case 'b':
            return White;
        case 'w':
            return Black;

        default:
            return Empty;
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
        if (grid[row][i] == convertSymbol(color)) {
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

bool Board::checkAllyDiag(const std::string &playerMove, char color) const {

}


