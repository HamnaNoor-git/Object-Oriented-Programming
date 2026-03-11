#include<iostream>
#include"25i3113_Lab07_2.h"
using namespace std;

BankAccount:: ~BankAccount()
{
	cout << "Account closed for: " << accountHolder;
}

void BankAccount::deposit(double amount)
{
	*balance +=amount;
}
void BankAccount::withdraw(double amount)
{
	if (*balance >= amount)
		*balance -= amount;
	else
		cout << "Insufficient balance\n";
}
double BankAccount::getBalance() const
{
	return *balance;
}
void BankAccount::display() const
{
	cout << "Account Number: " << accountNumber << endl
		 << "Account Holder: " << accountHolder << endl
		 << "Account Type: " << accountType << endl
		 << "Balance: " << *balance << endl;
}

BankAccount::BankAccount(int accountNumber, string accountHolder, string accountType, int intBalance)
{
	this->accountNumber = accountNumber;
	this->accountHolder = accountHolder;
	this->accountType = accountType;

	balance = new double;     // dynamic memory
	*balance = intBalance;

}
