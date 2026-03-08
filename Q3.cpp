#include<iostream>
using namespace std;

int* ColumnSums(int** projection, int rows, int cols)
{
	int* sum = new int[cols];
	for (int i = 0; i < cols; i++)
	{
		*(sum + i) = 0;
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			*(sum + i) += *(*(projection + j) + i);
		}
	}
	return sum;
}

int** TransposeProjection(int** projection, int rows, int cols)
{
	int** transpose = new int* [cols];
	for (int i = 0; i < cols; i++)
	{
		*(transpose + i) = new int[rows];
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			*(*(transpose + j) + i) = *(*(projection + i) + j);
		}
	}

	return transpose;
}

int** FlipHorizontal(int** projection, int rows, int cols)
{
	int** flip = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		*(flip + i) = new int[cols];
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			*(*(flip + i) + j) = *(*(projection + i) + cols - 1 - j);
		}
	}

	return flip;
}

int** FlipVertical(int** projection, int rows, int cols)
{
	int** flip = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		*(flip + i) = new int[cols];
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			*(*(flip + i) + j) = *(*(projection + (rows - 1 - i)) + j);
		}
	}

	return flip;
}

int** RotateProjection(int** projection, int rows, int cols, int degree)
{
	if (degree == 0)
	{
		return projection;
	}

	int** transposed = TransposeProjection(projection, rows, cols);
	int** rotation = FlipHorizontal(transposed, cols, rows);

	return RotateProjection(rotation, cols, rows, degree - 90);
}

int SumProjection(int** projection, int rows, int cols)
{
	int sum = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			sum += *(*(projection + i) + j);
		}
	}

	return sum;
}

int* RowSums(int** projection, int rows, int cols)
{
	int* sum = new int[rows];
	for (int i = 0; i < rows; i++)
	{
		*(sum + i) = 0;
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			*(sum + i) += *(*(projection + i) + j);
		}
	}

	return sum;
}

int*** GenerateProjections(int* spectrum, int size, int& count)
{
	//valid projections are d * r * c == size
	count = 0;
	for (int d = 1; d <= size; d++)
	{
		for (int r = 1; r <= size; r++)
		{
			for (int c = 1; c <= size; c++)
			{
				if (d * r * c == size)
				{
					count++;
				}
			}
		}
	}

	int*** AllProjections = new int** [count];

	int ap = 0;
	for (int d = 1; d <= size; d++)
	{
		for (int r = 1; r <= size; r++)
		{
			for (int c = 1; c <= size; c++)
			{
				if (d * r * c == size)
				{
					// Create 2D projection (d*r rows, c columns)
					int** row3D = new int* [d * r];

					for (int z = 0; z < d; z++)
					{
						for (int y = 0; y < r; y++)
						{
							int index = z * (r * c) + y * c;
							*(row3D + (z * r + y)) = spectrum + index;
						}
					}

					*(AllProjections + ap) = row3D;
					ap++;
				}
			}
		}
	}

	return AllProjections;
}

void print(int** projection, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << *(*(projection + i) + j) << " ";
		}
		cout << endl;
	}
}

void delete2D(int** arr, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] * (arr + i);
	}
	delete[] arr;
}


int main()
{
	cout << "Quantum Prism" << endl << endl;

	int size;
	cout << "Enter size of 1D spectrum: ";
	cin >> size;

	int* spectrum = new int[size];
	cout << "\nEnter " << size << " values for spectrum:" << endl;

	for (int i = 0; i < size; i++)
	{
		cout << "element " << i+1 << " = ";
		cin >> *(spectrum + i);
	}

	int count = 0;
	int*** allProjections = GenerateProjections(spectrum, size, count);

	cout << "Total valid 3D projections: " << count << endl;
	cout << "Projections" << endl;

	int projectionIndex = 0;
	for (int d = 1; d <= size; d++)
	{
		for (int r = 1; r <= size; r++)
		{
			for (int c = 1; c <= size; c++)
			{
				if (d * r * c == size)
				{
					int rows = d * r;
					int cols = c;

					cout << endl;

					int** projection = *(allProjections + projectionIndex);
					print(projection, rows, cols);

					projectionIndex++;
				}
			}
		}
	}

	if (count > 0)
	{
		cout << "\nProjection 1" << endl << endl;
		int rows = 1, cols = size;
		bool found = false;

		for (int d = 1; d <= size && !found; d++)
		{
			for (int r = 1; r <= size && !found; r++)
			{
				for (int c = 1; c <= size; c++)
				{
					if (d * r * c == size)
					{
						rows = d * r;
						cols = c;
						found = true;
						break;
					}
				}
			}
		}


		int** projection = *(allProjections + 0);

		//	Print original projection
		cout << " Initial (" << rows << "x" << cols << "):" << endl;
		print(projection, rows, cols);
		cout << endl;

		//	Column Sums
		cout << " coloumn sum:" << endl;
		int* colSums = ColumnSums(projection, rows, cols);
		for (int i = 0; i < cols; i++)
		{
			cout << "Col " << i << ": " << *(colSums + i) << " ";
		}
		cout << "\n\n";

		//	Row Sums
		cout << " row sum" << endl;
		int* rowSums = RowSums(projection, rows, cols);
		for (int i = 0; i < rows; i++)
		{
			cout << "Row " << i << ": " << *(rowSums + i) << " ";
		}
		cout << "\n\n";

		//	Total Sum
		cout << " total sum:" << endl;
		int totalSum = SumProjection(projection, rows, cols);
		cout << "Sum: " << totalSum << "\n\n";

		//	Transpose
		cout << " transposed (" << cols << "x" << rows << "):" << endl;
		int** transposed = TransposeProjection(projection, rows, cols);
		print(transposed, cols, rows);
		cout << endl;

		//	Flip Horizontal
		cout << " horizontal flip (" << rows << "x" << cols << "):" << endl;
		int** flippedH = FlipHorizontal(projection, rows, cols);
		print(flippedH, rows, cols);
		cout << endl;

		//	Flip Vertical
		cout << "vertical flip (" << rows << "x" << cols << "):" << endl;
		int** flippedV = FlipVertical(projection, rows, cols);
		print(flippedV, rows, cols);
		cout << endl;

		//	Rotate 90
		cout << "single rotation (" << cols << "x" << rows << "):" << endl;
		int** rotation = RotateProjection(projection, rows, cols, 90);
		print(rotation, cols, rows);
		cout << endl;

		//	Rotate 180
		cout << "double rotation (" << rows << "x" << cols << "):" << endl;
		int** rotated180 = RotateProjection(projection, rows, cols, 180);
		print(rotated180, rows, cols);
		cout << endl;

		//	Rotate 270
		cout << "triple rotation (" << cols << "x" << rows << "):" << endl;
		int** rotated270 = RotateProjection(projection, rows, cols, 270);
		print(rotated270, cols, rows);


		delete[] colSums;
		delete[] rowSums;
		delete2D(transposed, cols);
		delete2D(flippedH, rows);
		delete2D(flippedV, rows);
		delete2D(rotation, cols);
		delete2D(rotated180, rows);
		delete2D(rotated270, cols);
	}


	for (int i = 0; i < count; i++)
	{
		delete[] * (allProjections + i);
	}
	delete[] allProjections;
	delete[] spectrum;

	return 0;
}
