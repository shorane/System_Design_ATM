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
    void executeTransaction(int methodIdIn);
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
    while (!pinQuery(cardSerial, pinIn) && pinCount < PIN_THRESHOLD)
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
    cout << "3. Deposit Money" << endl;
    cout << "4. Transfer between accounts" << endl << "Select one of the above methods by serial number or enter 0 to exit" << endl;
    int methodId;
    cin >> methodId;
    if (methodId == 0) return 0;
    while (methodId > 4 || methodId < 1) 
    {
        cout << " Please enter a method number between 1 to 4" << endl;
        cin >> methodId;
        if (methodId == 0) return 0;
    }
    return methodId;
}

void ATM::executeTransaction(int methodIdIn)
{
    switch(methodIdIn)
    {
        int amount;
        long accNo;
        case(1): 
                accNo = this->accountSelectionMenu();
                if (accNo == 0) break;
                this->display(accNo); break;
        case(2):
                accNo = this->accountSelectionMenu();
                if (accNo == 0) break;         
                cout << "Please enter amount to withdraw" << endl;
                cin >> amount;
                this->withdraw(accNo, amount); break;
        case(3):
                accNo = this->accountSelectionMenu();
                if (accNo == 0) break;     
                cout << "Please enter amount to deposit" << endl;
                cin >> amount;
                this->deposit(accNo, amount); break;
        case(4):
                cout << "Please select account to transfer FROM: " << endl;
                long fromAcc = this->accountSelectionMenu();
                if (fromAcc == 0) break;
                cout << "Please select account to transfer TO:" << endl;
                long toAcc = this->accountSelectionMenu();  
                if (toAcc == 0) break;
                if (toAcc == fromAcc) cout << "Warning: you are transfering to the same account" << endl;
                cout << "Please enter amount to transfer" << endl;
                cin >> amount;
                cout << "For withdrawal account: " << endl;
                this->withdraw(fromAcc, amount);
                cout << "For deposit account: " << endl;
                this->deposit(toAcc, amount);
                break;

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
