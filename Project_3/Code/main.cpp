#include "user.h"
#include <iostream>

using namespace std;

int main()
{
    //Create user
    User u1("john");
    User u2("mary");

    //Create account
    Account &a1 = u1.getAccount();

    //User's ID
    cout << "u1's id = " << u1.getID() << endl;
    cout << "u2's id = " << u2.getID() << endl;

    //Account deposit
    a1.deposit(400);
    cout << "john deposit 400 dollars." << endl;
    cout << "Balance of " << u1.getUsername() << " account is " << a1.getAmount() << endl;

    //Account withdraw
    a1.withdraw(100);
    cout << "john withdraw 100 dollars." << endl;
    cout << "Balance of " << u1.getUsername() << " account is " << a1.getAmount() << endl;

    //Account transferMoney
    a1.transferMoney(u2.getAccount(), 200);
    cout << "john transfer 200 dollars to mary." << endl;
    cout << "Balance of " << u1.getUsername() << " account is " << a1.getAmount() << endl;
    cout << "Balance of " << u2.getUsername() << " account is " << u2.getAccount().getAmount() << endl;

    ////Account transferMoney
    u2.getAccount().transferMoney(a1, 100);
    cout << "mary transfer 100 dollars to john." << endl;
    cout << "Balance of " << u1.getUsername() << " account is " << a1.getAmount() << endl;
    cout << "Balance of " << u2.getUsername() << " account is " << u2.getAccount().getAmount() << endl;

    //User Details
    u1.get_trans();
    u2.get_trans();

}
