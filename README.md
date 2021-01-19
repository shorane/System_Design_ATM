# ATM Controller System Design

## Running the project
The code compiles under gcc 4.8.4 with optimization level 1. Enter below command to compile the code:

	g++ -std=c++11 -O1 driver.cpp -o main

To run the program, enter the below command:
	
	./main

Follow the instructions displayed to go through the process of performing a transaction with the ATM API.
Correct security pin to proceed with the transaction is 1111. Further instructions for using the program will be displayed after entering the pin.

## Example run:
```
Enter 4 digit pin number or enter 0 to exit:
```
User input: 1111
```
Pin verification successfull
Select one of the below accounts by serial number or enter 0 to exit: 
1. 1233
2. 1232
3. 1231
```
User input: 3
```
What would you like to do today
1. See Balance
2. Withdraw Money
3. Deposit Money
Select one of the above methods by serial number or enter 0 to exit
```
User input: 2
```
Please enter amount to withdraw
```
User input: 100
```
Amount before transaction: 599
Amount after transaction: 499
Transaction completed! Would you like to perform another transaction? 
yes/no?
```
User input: no
```
Thank you for banking with us. Have a nice day!
```

## About the project
The project consists of the 4 following files.

**1. Driver.cpp**
This is the main script of the project. It is responsible for carrying out all the procedures and methods necessary to carry out a successful transaction which consists of the following steps.

Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw

- The script first instantiates dummy accounts (whose details are stored in bankAPI.h) and then makes an instance of the class simpleATM. This simulates card insertion and saves the user's card serial (here hardcoded to be "1"). Then the user is asked for the pin by calling the function pinCheck on the instance of the class simpleATM. As part of the dummy data, the correct pin for the card with serial number 1 is 1111.
- If the pin check is successful (within 3 tries) it asks for which account the user wants to carry out the transaction. All the existing accounts of the user are shown.
- Once the user has selected the account he/she is then asked to select the transaction they want to carry out amongst checking balance, deposit, and withdrawal.

**2. ATM.h**
This script acts as the ATM machine. It accepts commands from Driver.cpp (user inputs) and communicates with the bankAPI which in turn has all the bank records like cardSerial number, name of the user, pin and all the user accounts along with their respective balances.
- Constructor simpleATM is invoked when card is inserted which creates an instance of type simpleATM.
- The function pinCheck() is invoked from Driver.cpp which in turn calls pinQuery declared in bankAPI.h and passes card serial number and pin number entered by the user as function arguments. The pinQuery takes the pin input and checks the it against pin stored in the bank database for that particular card serial number.
- If so the control is returned to Driver.cpp otherwise the user is given 2 more tries after which the session is terminated.
- The program also has functions for account selection, choosing a method and also displaying or updating balance. In all of these functions, SimpleATM.h just acts as an interface between the user and bankAPI. It never has access to the bank records directly but can only request modification or account information thus enforcing abstraction.

**3. cardHolderStruct.h**
It simply has the structure which holds the user's data. It has the following data members.
- long cardSerial: Serial id of the card which is obtained when the user swipes their card on the ATM machine.
- string name: Name of the card holder.
- int pin: pin for the card.
- unordered_map<long,long> accounts: The map stores account name as the key and it's balance as value for that key. This is implemented in the form of an unordered map as a card holder can have multiple accounts and addition, removal, or finding the account is very fast to compute and easy to implement in the form of unordered_map.
 
**3. bankAPI.h**
This file acts as the central database and also handles all transactions and requests from SimpleATM.h. It has functions that initialize the dummy accounts, checks the input pin obtained from simpleATM.h against the true pin stored in the database, and display or modify balance in the accounts.
The bankAPI functions are seperated away from the class functions of the ATM class to mimick realistic behavior, where the ATM client just queries the bank server for information, or to make changes to the balance of the card holder. Hence, the bankAPI functionality can be thought of as a bank server.
