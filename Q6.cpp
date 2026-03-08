#include <iostream>
#include <ctime>
using namespace std;

char toLowerChar(char c)
{
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

char toUpperChar(char c)
{
    if (c >= 'a' && c <= 'z') return c - 32;
    return c;
}

bool charEqualIgnoreCase(char a, char b)
{
    return toLowerChar(a) == toLowerChar(b);
}

void fillMazeRecursive(char** maze, int rows, int cols, int r, int c)
{
    if (r == rows) 
        return;
    if (c == cols) 
    {
        fillMazeRecursive(maze, rows, cols, r + 1, 0);
        return;
    }
    maze[r][c] = 'a' + (rand() % 26);
    fillMazeRecursive(maze, rows, cols, r, c + 1);
}

void displayMazeRecursive(char** maze, int rows, int cols, int r, int c)
{
    if (r == rows) 
        return;
    if (c == cols) 
    {
        cout << endl;
        displayMazeRecursive(maze, rows, cols, r + 1, 0);
        return;
    }
    cout << maze[r][c] << " ";
    displayMazeRecursive(maze, rows, cols, r, c + 1);
}

void freeMazeRecursive(char** maze, int rows, int r)
{
    if (r == rows) 
    {
        delete[] maze;
        return;
    }
    delete[] maze[r];
    freeMazeRecursive(maze, rows, r + 1);
}

bool isOutOfBounds(int r, int c, int rows, int cols)
{
    if (r < 0 || c < 0 || r >= rows || c >= cols) 
        return true;
    
    return false;
}

bool searchDir(char** maze, int rows, int cols, char* word, int r, int c, int dr, int dc, int idx)
{
    if (word[idx] == '\0') 
        return true;

    if (isOutOfBounds(r, c, rows, cols)) 
        return false;
    
    if (!charEqualIgnoreCase(maze[r][c], word[idx])) 
        return false;
 
    return searchDir(maze, rows, cols, word, r + dr, c + dc, dr, dc, idx + 1);
}

void capitalizeDir(char** maze, char* word, int r, int c, int dr, int dc, int idx)
{
    if (word[idx] == '\0') 
        return;

    maze[r][c] = toUpperChar(maze[r][c]);
    capitalizeDir(maze, word, r + dr, c + dc, dr, dc, idx + 1);
}

bool searchAllDirections(char** maze, int rows, int cols, char* word, int r, int c, int d)
{
    int dr[8] = { 0,0,1,-1,1,-1,1,-1 };
    int dc[8] = { 1,-1,0,0,1,-1,-1,1 };
    if (d == 8) 
        return false;
    
    if (searchDir(maze, rows, cols, word, r, c, dr[d], dc[d], 0))
    {
        capitalizeDir(maze, word, r, c, dr[d], dc[d], 0);
        return true;
    }
    return searchAllDirections(maze, rows, cols, word, r, c, d + 1);
}

void startGame()
{
    int rows = 8, cols = 8;
    char** maze = new char* [rows];
    for (int i = 0; i < rows; i++)
        maze[i] = new char[cols];

    fillMazeRecursive(maze, rows, cols, 0, 0);
    cout << "\nInitial Maze:\n";
    displayMazeRecursive(maze, rows, cols, 0, 0);

    char word[50];
    int r, c;
    cout << "\nEnter word to search: ";
    cin >> word;
    cout << "Enter starting row: ";
    cin >> r;
    cout << "Enter starting col: ";
    cin >> c;

    if (searchAllDirections(maze, rows, cols, word, r, c, 0))
        cout << "\nWord FOUND!\n";
    else
        cout << "\nWord NOT FOUND!\n";

    cout << "\nFinal Maze:\n";
    displayMazeRecursive(maze, rows, cols, 0, 0);

    freeMazeRecursive(maze, rows, 0);
}

int main()
{
    srand(time(0));
    int choice;

    do {
        cout << "\nWORD SEARCH MAZE       \n";
        cout << "==============================\n";
        cout << "  1. Start Game\n";
        cout << "  2. Exit\n";
        cout << "\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            startGame();
            break;
        case 2:
            cout << "\nGoodbye!\n";
            break;
        default:
            cout << "\nInvalid choice. Please enter 1 or 2.\n";
        }

    } while (choice != 2);

    return 0;
}