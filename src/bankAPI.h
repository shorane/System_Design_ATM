#pragma once
#include <iostream>
#include <array>
#include <memory>
#include "cardHolderStruct.h"
#define MAX_CARDHOLDERS 10

/* Functions in this file
void                            make_dummy_accounts     ()
std::shared_ptr<cardholder>     getCardholder           (long cardSerialIn)
bool                            pinQuery                (long cardSerialIn, int pinIn)
std::unordered_map<long,long>   getCarholderAccounts    (long cardSerialIn)
long                            getBal                  (long cardSerialIn, long accNoIn)
void                            updateBal               (long cardSerialIn, long accNoIn, long amountIn)
*/

// pointer to bank accounts data structure
std::shared_ptr<std::array<cardholder,MAX_CARDHOLDERS> > bankAccounts (new std::array<cardholder,MAX_CARDHOLDERS>);


// Definition of functions

void make_dummy_accounts(){
    *bankAccounts = 
    {{
        //  { card serial | holder name | security pin | account number and cash balance pairs    }
            {   1,         "Holder 1",     1111,       { {1231, 599}, {1232, 346}, {1233, 530} } },
            {   2,         "Holder 2",     2222,       { {4561, 345}, {4562, 578}, {4563, 405} } },
            {   3,         "Holder 3",     3333,       { {7891, 157}, {7892, 234}, {7893, 846} } },
    }};
}

std::shared_ptr<cardholder> getCardholder(long cardSerialIn)
{
    for (auto& acc:*bankAccounts)
    {
        if (acc.cardSerial == cardSerialIn)
        {
            std::shared_ptr<cardholder> temp (new cardholder(acc));
            return temp;
        }
    }
    return nullptr;
}

bool pinQuery(long cardSerialIn, int pinIn)
{
    std::shared_ptr<cardholder> thisCardHolder = getCardholder(cardSerialIn);
    if (thisCardHolder->pin == pinIn) return true;
    return false;
}

std::unordered_map<long,long> getCarholderAccounts(long cardSerialIn)
{
    std::shared_ptr<cardholder> thisCardHolder = getCardholder(cardSerialIn);
    return thisCardHolder->accounts;
}

long getBal(long cardSerialIn, long accNoIn)
{
    std::shared_ptr<cardholder> thisCardHolder = getCardholder(cardSerialIn);
    return thisCardHolder->accounts[accNoIn];
}

void updateBal(long cardSerialIn, long accNoIn, long amountIn)
{
    for(auto& acc: *bankAccounts)
    {
        if (acc.cardSerial == cardSerialIn)
        {
            std::cout << "Amount before transaction: " << acc.accounts[accNoIn] << std::endl;
            if (acc.accounts[accNoIn] + amountIn < 0) std::cout << "Insufficient funds in your account. Transaction failed." << std::endl;
            else acc.accounts[accNoIn] += amountIn;
            std::cout << "Amount after transaction: " << acc.accounts[accNoIn] << std::endl;
        }
    }
}