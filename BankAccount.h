#pragma once
#include <string>
using namespace std;
class BankAccount
{
	int accountNumber;
	string accountHolder;
	string accountType;
	double* balance;

public:
	void deposit(double amount);
	void withdraw(double amount);
	double getBalance() const;
	void display() const;
	~BankAccount();
	BankAccount(int accountNumber, string accountHolder, string accountType, int intBalance = 0);
};