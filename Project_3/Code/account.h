
class Account
{
  private:
		int ID, amount, trans_num = 0;  //trans_num is the number of transaction of this account
		char *user_name;  //name of the User who owns this account
		char trans[100][55] = {{0}};  //log of transaction of this account

  public:

		//constructor
		Account();
		Account(int want_amount, int want_ID);

		//Account operations
		bool withdraw(int deductAmount);
		bool deposit(int addAmount);
		bool transferMoney(Account &AccountOfB, int amountToTransfer);

		//Check account balance
		int getAmount();

		void load_name(char *name); //load user name from User who owns this account
		char *get_user_name(); //return user_name 
		int get_trans_num(); //return trans_num
		char *get_trans(int k); //return k_th transaction

		//Destructor
		~Account();
};
