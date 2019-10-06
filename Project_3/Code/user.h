#include "Transaction.h"

class User
{
  private:

		char name[16] = {0};
		int ID, trans_num = 0;
		static int user_num; //number of times of calling constructor, and let it be user's id
		Transaction *trans[100];
		Account account;

  public:

		//constructor
		User(const char *want_name);

		//User operations
		char *getUsername();
		Account &getAccount();
		int getID();

		// print the log of transaction
		void get_trans();

		//Destructor
		~User();
};
