#include<iostream>
#include<cmath>
using namespace std;

//placement checks
bool placement(int** board, int n, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		if (board[i][col] == 1)
			return false;
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == 1)
			{
				if (abs(row - i) == abs(col - j))
					return false;
			}

		}
	}

	return true;

}
bool royalHarmony(int**& board, int row, int column, int queens)
{
	if (row == queens)
	{
		return true;
	}

	if (column == queens)
	{
		return false;
	}

	if (placement(board, queens, row, column))
	{
		board[row][column] = 1;

		if (royalHarmony(board, row + 1, 0, queens))
		{
			return true;
		}

		board[row][column] = 0; 
	}

	//next
	return royalHarmony(board, row, column + 1, queens);
}


int main()
{
	int n;
	cout << "enter Number of queens: ";
	cin >> n;

	//DMA 
	int** arr = new int* [n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[n];
	}

	//initialize to 0
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arr[i][j] = 0;
		}
	}

	bool solved = royalHarmony(arr, 0, 0, n);

	if (solved)
	{
		cout << "placement of Queens:" << endl;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}

	else
		cout << " no solution";

}
