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


square_state Board::get(const char row,const char col) const
{
    int numCol = convertCol(col);
    if (check(row,numCol))
    {
        return err;
    }
    return grid[row - 1][numCol - 1];
}

void Board::set(const int row, const char col, const square_state state)
{
    int numCol = convertCol(col);
    if (check(row, numCol) && state != err)
    {
        grid[row - 1][numCol - 1] = state;
    }
}

bool Board::flip(const int row, const char col)
{

}

bool Board::insert(string& playerMove)
{

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
    return row > 1 && row < 8 && col > 'A' && col < 'H';
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
