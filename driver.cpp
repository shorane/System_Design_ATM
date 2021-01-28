#include <iostream>
#include <memory>
#include "ATM.h"

using namespace std;

int main()
{
    // make dummy accounts for testing purposes
    make_dummy_accounts();

    // insert card => create  atm instance
    shared_ptr<ATM> atmInstance (new ATM(1));   // let 1 be the card serial number
    bool running = true;

    // enter pin and check against actual pin
    if (atmInstance -> pinCheck() == false)
    {
        cout << "Session terminated" << endl;
        running = false;
    }

    // if pin correct, continue session

    while (running)
    {
        // display all accounts, ask for a number like 1,2,3
        long accNo = atmInstance->accountSelectionMenu();
        if (accNo == 0) break;

        // ask for one of three methods, (perform validity checks of input just like above)
        int methodId = atmInstance->methodSelectionMenu();
        if (methodId == 0) break;

        // perform the transaction method (see balance, deposit or withdrawal)
        atmInstance->executeTransaction(methodId, accNo);

        cout << "Transaction completed! Would you like to perform another transaction? " << endl << "yes/no?" << endl;
        string option;
        cin >> option;
        if (option == "no") running = false; 
    }   
    cout << "Thank you for banking with us. Have a nice day!!" << endl;
    return 0;
}