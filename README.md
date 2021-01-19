# ATM_controller

## Running the project
The code compiles under gcc 4.8.4 with optimization level 1. Enter below command to compile the code:

	g++ -std=c++11 -O1 driver.cpp -o main

To run the program, enter the below command:
	
	./main

Follow the instructions displayed to go through the process of performing a transaction with the ATM API

## About the project
The project consists of the 4 following files.

**1. Driver.cpp**
This is the main script of the project. It is responsible for carrying out all the procedures and methods necessary to carry out a successful transaction which consists of the following steps.
Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw
- The script first instantiates dummy accounts (whose details are stored in bankAPI.h) and then makes an instance of the class simpleATM. This simulates card insertion and saves the user's card serial (here 1). Then the user is asked for the pin by calling the function pinCheck on the instance of the class simpleATM.
- If the pin check is successful (within 3 tries) it asks for which account the user wants to carry out the transaction. All the existing accounts of the user are shown.
- Once the user has selected the account he/she is then asked to select the transaction they want to carry out amongst checking balance, deposit, and withdrawal.

**2. SimpleATM.h**
This script acts as the ATM machine. It commands from Driver.cpp (user inputs) and communicates with the bankAPI which in turn has all the bank records like cardSerial number, name of the user, pin and all the user accounts along with their respective balances.
- Constructor simpleATM is invoked when card is inserted which creates an instance of type simpleATM.
- The function pinCheck() is invoked from Driver.cpp which in turn calls pinQuery declared in bankAPI.h and passes card serial number and pin number entered by the user as function arguments. The pinQuery takes the pin input and checks the it against pin stored in the bank database for that particular card serial number.
- If so the control is returned to Driver.cpp otherwise the user is given 2 more tries after which the session is terminated.
- The program also has functions for account selection, choosing a method and also displaying or updating balance. In all of these functions, SimpleATM.h just acts as an interface between the user and bankAPI. It never has access to the bank records directly but can only request modification or account information thus enforcing abstraction.

**3. bankDetails.h**
It simply has the structure which holds the user's data. It has the following data members.
- long cardSerial: Serial id of the card which is obtained when the user swipes their card on the ATM machine.
- string name: Name of the card holder.
- int pin: pin for the card.
- unordered_map<long,long> accounts: The map stores account name as the key and it's balance as value for that key. This is implemented in the form of an unordered map as a card holder can have multiple accounts and addition, removal, or finding the account is very fast to compute and easy to implement in the form of unordered_map.
 
**3. bankDetails.h**
This file acts as the central database and also handles all transactions and requests from SimpleATM.h. It has functions that initialize the dummy accounts, checks the input pin obtained from simpleATM.h against the true pin stored in the database, and display or modify balance in the accounts.


