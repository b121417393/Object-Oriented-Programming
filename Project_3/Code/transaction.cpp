#include "Transaction.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

//Default constructor
Transaction::Transaction()
{
}

//Constructor
Transaction::Transaction(Account &want_account, const char *want_type)
{
	strcpy(type, want_type);
	cout << "Transaction constructed" << endl;
}

//print type
void Transaction::print()
{
	cout << type << endl;
	return;
}

//destructor
Transaction::~Transaction()
{
	cout << "Transaction destructed" << endl;
}
