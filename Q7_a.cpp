#include <iostream>
using namespace std;

void printChar(char c, int n) 
{
    if (n <= 0) return;
    cout << c << " ";
    printChar(c, n - 1);
}

void row(int spaces, int dots, int stars) 
{
    printChar(' ', spaces);

    //Left 
    cout << "# ";
    printChar('.', dots);
    printChar('*', stars);

    //Center
    cout << "| ";

    //Right
    printChar('*', stars);
    printChar('.', dots);
    cout << "#" << endl;
}

void helperFunc(int totalRows, int startCols, int current) 
{
    int spaces = (totalRows - 1) - current;
    int dots = startCols - current;
    int stars = 2 * current;

    if (current == totalRows - 1) 
    {
        row(spaces, dots, stars);
        return;
    }

    row(spaces, dots, stars);           
    helperFunc(totalRows, startCols, current + 1); 
    row(spaces, dots, stars);          
}

void RecursivePattern3(int rows, int columns) 
{
    helperFunc(rows, columns, 0);
}

int main() 
{
    int n;
    cout << "enter a number for rows and coloumn: ";
    cin >> n;
    RecursivePattern3(n, n);
    return 0;
}
