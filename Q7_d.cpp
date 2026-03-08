#include <iostream>
#include <cmath>
using namespace std;


int validSize(int n)
{
    if (n < 3)
        return 3;

    int power = (int)(log(n) / log(3));
    return pow(3, power);
}


char relatedCh(int r, int c, int size)
{
    if (size == 3) {
        if (r == 1 && c == 1)
            return 'X';

        if (r == c)
            return '\\';

        if (r + c == 2)
            return '/';

        return ' ';
    }

    int shape_s = size / 3;
    int quad_r = r / shape_s;
    int quad_c = c / shape_s;


    if ((quad_r == quad_c) || (quad_r + quad_c == 2))
    {
        return relatedCh(r % shape_s, c % shape_s, shape_s);
    }
    else {
        return ' ';
    }
}

void print_row(int r, int c, int size)
{
    if (c == size)
        return;

    cout << relatedCh(r, c, size);
    print_row(r, c + 1, size);
}

void printLoop(int r, int size)
{
    if (r == size)
        return;

    print_row(r, 0, size);
    cout << "\n";
    printLoop(r + 1, size);
}

int main() {
    int input;
    cout << "enter number with power of 3: ";
    cin >> input;

    int size = validSize(input);
    printLoop(0, size);

    return 0;
}
