#pragma once
#include <string>
#include <unordered_map>

struct cardholder
{   
    long cardSerial;                        // card serial number
    std::string name;                       // name of the card holder
    int pin;                                // the security pin associated with the card
    std::unordered_map<long,long> accounts; // hash table containing the balance in each account
};


/* 
Each cardholder can have multiple accounts with their bank, 
for instance savings, checking, current. 
A hashmap is used to store and link this information.
*/