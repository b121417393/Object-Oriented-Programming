#include "account.h"

class Transaction
{
  private:
	
		char type[55] = {0};
		int amount;
		Account account;

  public:

  	//constructor
		Transaction();
		Transaction(Account &want_account, const char *want_type);

		//Transaction operation
		void print();

		//Destructor
		~Transaction();
};
