#include "account.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

//Default constructor
Account::Account(){};

//Constructor
Account::Account(int want_amount, int want_ID)
{
	amount = want_amount;
	ID = want_ID;
	cout << "Account constructed" << endl;
}

//deposit
bool Account::deposit(int addAmount)
{
	amount += addAmount;

	sprintf(trans[trans_num], "Type: Deposit %d", addAmount); //record transaction
	trans_num++;
	
	return true;
}

//withdraw
bool Account::withdraw(int deductAmount)
{
	if (deductAmount < 0)
		return false;
	if (amount >= deductAmount)
	{
		sprintf(trans[trans_num], "Type: Withdraw %d", deductAmount); //record transaction
		trans_num++;

		amount -= deductAmount;
		return true;
	}
	return false;
}

//get amount
int Account::getAmount()
{
	return amount;
}

//transfer Money
bool Account::transferMoney(Account &AccountOfB, int amountToTransfer)
{
	if (amountToTransfer < 0)
		return false;
	if (amount >= amountToTransfer) //if there's enough money
	{
		sprintf(trans[trans_num], "Type: Transferred %d to %s", amountToTransfer, AccountOfB.get_user_name()); //record transaction
		trans_num++;

		amount -= amountToTransfer;
		AccountOfB.deposit(amountToTransfer); //transfer money to AccountOfB
		return true;
	}

	return false;
}

//get user name
char *Account::get_user_name()
{
	return user_name;
}

//load user name
void Account::load_name(char *name)
{
	user_name = name;
}

//get transfer numbers
int Account::get_trans_num()
{
	return trans_num;
}

//get detail
char *Account::get_trans(int k)
{
	return trans[k];
}

//destructor
Account::~Account()
{
	cout << "Account destructed" << endl;
}
