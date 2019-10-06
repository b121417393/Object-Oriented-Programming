#include "user.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int User::user_num=0; 

//constructor
User::User(const char *want_name)
	: account(0, user_num) 
{

	strcpy(name, want_name);
	
	ID = user_num;
	user_num++;
	
	account.load_name(name); //give user's name to account

	cout << "new user " << name << " created" << endl;
}

//get account
Account &User::getAccount()
{
	return account;
}

//get ID
int User::getID()
{
	return ID;
}

//get user name
char *User::getUsername()
{
	return name;
}

//print transaction details
void User::get_trans()
{
	//update the transaction log from account's transaction log
	if (trans_num < account.get_trans_num()) 
	{
		//this means there're some transaction log in account but not in user
		for (int i = trans_num; i < account.get_trans_num(); i++)
			trans[i] = (new Transaction(account, account.get_trans(i)));

		trans_num = account.get_trans_num();
	}

	cout << name << "'s log of transaction" << endl;
	cout << "Type: Create" << endl;
	for (int i = 0; i < trans_num; i++)
		(*trans[i]).print();
}

//destructor
User::~User()
{
	for (int i = 0; i < trans_num; i++)
		delete trans[i];

	cout << "User destructed" << endl;
}
