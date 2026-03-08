#include <iostream>
using namespace std;

bool isValid(int grid[9][9], int row, int col, int num)
{
    //row
    for (int j = 0; j < 9; j++)
    {
        if (grid[row][j] == num)
            return false;
    }

    //coloumn
    for (int i = 0; i < 9; i++)
    {
        if (grid[i][col] == num)
            return false;
    }

    // 3x3 box
    int box_row = (row / 3) * 3;
    int box_col = (col / 3) * 3;
    for (int i = box_row; i < box_row + 3; i++)
    {
        for (int j = box_col; j < box_col + 3; j++)
        {
            if (grid[i][j] == num)
            {
                return false;
            }
        }
    }

    return true;
}

bool findEmptyCell(int grid[9][9], int& row, int& col)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (grid[i][j] == 0)
            {
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

int solveSudoku(int grid[9][9])
{

    int row = -1, col = -1;

    if (!findEmptyCell(grid, row, col))
        return 1;

    for (int num = 1; num <= 9; num++)
    {
        if (isValid(grid, row, col, num))
        {
            grid[row][col] = num;       
            
            if (solveSudoku(grid) == 1)    
            {
                return 1;
            }

            grid[row][col] = 0;            
        }
    }
    return -1; 
}

int main() 
{
    //int grid[9][9] = {
    //    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    //    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    //    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    //    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    //    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    //    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    //    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    //    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    //    {0, 0, 0, 0, 8, 0, 0, 7, 9}
    //};

    int grid[9][9];
    cout << "enter 81 values for Initial grid:" << endl;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> grid[i][j];
        }
    }

    cout << endl << "Initial grid:" << endl;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << grid[i][j] << " | ";
        }
        cout << endl;
    }

    int result = solveSudoku(grid);

    if (result == 1)
    {
        cout << endl << "Solution Found!" << endl;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cout << grid[i][j] << " | ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "No solution! (-1) " << endl;
    }

    return 0;
}
