#include <iostream>
#include <iomanip>
using namespace std;


int index(int n, int r, int c, int offset) {
    
    int lastIdx = n - 1 - offset;

    // Top 
    if (r == offset && c >= offset && c <= lastIdx)
    {
        return c - offset;
    }
    // Right 
    if (c == lastIdx && r > offset && r <= lastIdx)
    {
        return (n - 1 - 2 * offset) + (r - offset);
    }
    // Bottom 
    if (r == lastIdx && c < lastIdx && c >= offset)
    {
        return 2 * (n - 1 - 2 * offset) + (lastIdx - c);
    }
    // Left 
    if (c == offset && r < lastIdx && r > offset)
    {
        return 3 * (n - 1 - 2 * offset) + (lastIdx - r);
    }

    
    return 4 * (n - 1 - 2 * offset) + index(n, r, c, offset + 1);
}


void cols(int n, int r, int c, int startNum)
{
    if (c == n)
    {
        return;
    }

    int step = index(n, r, c, 0);


    if (startNum == 1)
    {
        cout << setw(10) << fib(step + 1) << " ";
    }
    else 
    {
        cout << setw(5) << (startNum + step) << " ";
    }

    cols(n, r, c + 1, startNum);
}

void rows(int n, int r, int startNum)
{
    if (r == n) return; // Base case: end of rows

    cols(n, r, 0, startNum);
    cout << endl;

    rows(n, r + 1, startNum); // Recursive call for next row
}

long long fib(int k)
{
    static long long fibon[400] = { 0 };
    if (k <= 2) return 1;
    if (fibon[k] != 0) return fibon[k];
    return fibon[k] = fib(k - 1) + fib(k - 2);
}


int main() {
    int n, start;

    cout << "Enter size (n >= 5): ";
    cin >> n;

    cout << "Enter starting number: ";
    cin >> start;

    cout << "\nGenerated Spiral:\n" << endl;
    rows(n, 0, start);

    return 0;
}
