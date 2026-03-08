#include<iostream>
using namespace std;

void reverseBytes(char* inputBytes, int size, char* hexOutput)
{
	for (int i = 0; i < size; i++)
	{
		hexOutput[size - i - 1] = inputBytes[i];
	}
}

int main()
{
	int n;

	cout << "enter any value for n: ";
	cin >> n;
	char* inputBytes = NULL;
	inputBytes = (char*)&n;

	const int size = sizeof(int);
	char hexOutput[size];

	reverseBytes(inputBytes, size, hexOutput);
	int reversedValue = *(int*)hexOutput;
	cout << "Original n: " << n << endl;
	cout << "Original bytes: 0x";
	for (int i = 0; i < size; i++)
	{
		cout << (int)inputBytes[i] << "";
	}
	cout << endl;
	cout << "Reversed-bytes value: " << reversedValue << endl;




	

}
