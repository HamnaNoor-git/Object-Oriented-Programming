#include<iostream>
using namespace std;

//parameter given in question
void printVortex(int layers, char state1, char state2);

//functions

void space(int ind)
{
	if (ind <= 0)
		return;

    cout << " ";
	space(ind - 1);
	
}


void ucol(int n, char state)
{
	if (n <= 0)
		return;

    cout << state;
	ucol(n - 1, state);
}


// Upper 
void urow(int n, char state1, char state2, int s, int max_n) 
{
    if (n < 1) return;

    space(s);

 
    if (((max_n - n) / 2) % 2 == 0)
        ucol(n, state1);

    else
        ucol(n, state2);

    cout << endl;
    urow(n - 2, state1, state2, s + 1, max_n);
}

// Lower 
void lrow(int n, char state1, char state2, int s, int max_n) 
{
    if (n > max_n) 
        return;

    space(s);

    if (((max_n - n) / 2) % 2 == 0)
        ucol(n, state1);

    else
        ucol(n, state2);

    cout << endl;
    lrow(n + 2, state1, state2, s - 1, max_n);
}

void printVortex(int layers, char state1, char state2) 
{
    int maxWidth = (2 * layers) - 1;

    urow(maxWidth, state1, state2, 0, maxWidth);

    lrow(3, state1, state2, layers - 2, maxWidth);
}

int main() {
    int l;
    char c1, c2;
    cout << "enter length to print vortex: ";
    cin >> l;
    cout << "enter character 1: ";
    cin >> c1;
    cout << "enter character 2: ";
    cin >> c2;

    printVortex(l, c1, c2);
    return 0;
}














