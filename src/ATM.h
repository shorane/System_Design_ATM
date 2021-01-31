#pragma once
#include <iostream>
#include <vector>
#include "bankAPI.h"
#define PIN_THRESHOLD 3


using namespace std;

class ATM{
    // members
    long cardSerial;

public:
    //constructors
    ATM(long serialIn): cardSerial(serialIn) {};
    
    // member functions
    int getPin();
    bool pinCheck();
    long accountSelectionMenu();
    int methodSelectionMenu();
    void executeTransaction(int methodIdIn, int accNoIn);
    void display(long accNo);
    void withdraw(long accNo, long amountIn);
    void deposit(long accNo, long amountIn);
};

// Definition of member functions
int ATM::getPin()
{
    cout << "Enter 4 digit pin number or enter 0 to exit: " << endl;
    int pin;
    cin >> pin;
    return pin;
}

bool ATM::pinCheck()
{
    int pinCount = 1;
    int pinIn = getPin(); 
    if (pinIn == 0) return false;
    if (pinQuery(cardSerial, pinIn))
    {
        cout << "Pin verification successfull" << endl;
        return true;
    }
    while (!pinQuery(cardSerial, pinIn) and pinCount < PIN_THRESHOLD)
    {
        cout << "pinCount" << pinCount << endl;
        cout << "Incorrect Pin, you have " << PIN_THRESHOLD - pinCount << " tries left" << endl;
        ++pinCount;
        pinIn = getPin(); 
        if (pinIn == 0) return false;
        if (pinQuery(cardSerial, pinIn))
        {
            cout << "Pin verification successfull" << endl;
            return true;
        }
    }
    cout << "You have exhausted the number of retries. Goodbye" << endl;
    return false;
}

long ATM::accountSelectionMenu()
{
    // retrieve all accounts
    unordered_map<long,long> accs = getCarholderAccounts(cardSerial);
    
    int count = 0;
    vector<long> tempAcc;

    // store all accounts in a temp vector and display for selection
    cout << "Select one of the below accounts by serial number or enter 0 to exit: " << endl;
    for(auto& acc:accs)
    {
        cout << count+1 << ". " << acc.first << endl;
        tempAcc.push_back(acc.first);
        ++count;
    }
    
    // accept input with validity check
    int num;
    cin >> num;
    if (num == 0) return 0;
    while (num > tempAcc.size())
    {
        cout << "Please enter a valid account option" << endl;
        cin >> num;
        if (num == 0) return 0;
    }
    return tempAcc[num-1];
}

int ATM::methodSelectionMenu()
{
    cout << "What would you like to do today" << endl;
    cout << "1. See Balance" << endl;
    cout << "2. Withdraw Money" << endl;
    cout << "3. Deposit Money" << endl << "Select one of the above methods by serial number or enter 0 to exit" << endl;
    int methodId;
    cin >> methodId;
    if (methodId == 0) return 0;
    while (methodId > 3 or methodId < 1) 
    {
        cout << " Please enter a method number between 1 to 3" << endl;
        cin >> methodId;
        if (methodId == 0) return 0;
    }
    return methodId;
}

void ATM::executeTransaction(int methodIdIn, int accNoIn)
{
    switch(methodIdIn)
    {
        int amount;
        case(1): this->display(accNoIn); break;
        case(2): 
                cout << "Please enter amount to withdraw" << endl;
                cin >> amount;
                this->withdraw(accNoIn, amount); break;
        case(3): 
                cout << "Please enter amount to deposit" << endl;
                cin >> amount;
                this->deposit(accNoIn, amount); break;        
    }
}

void ATM::display(long accNo)
{
    long balance = getBal(cardSerial, accNo);
    cout << " Your current balance is: " << balance << endl;
}

void ATM::withdraw(long accNo, long amountIn)
{
    updateBal(cardSerial, accNo, -1*amountIn);
}

void ATM::deposit(long accNo, long amountIn)
{
    updateBal(cardSerial, accNo, amountIn);
}
