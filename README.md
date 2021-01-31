# ATM Controller System Design
A console based ATM implementation in C++.

Session flow: Insert Card => Enter PIN number => Select Account => See Balance/Deposit/Withdraw

## Running the project using gcc compiler
The code compiles under gcc 4.8.4 with optimization level 1. 

Set the terminal/command prompt working directory to the src folder in the project folder.

Enter below command to compile the code:
```
	g++ -std=c++11 -O1 driver.cpp -o main
```
To run the program, enter the below command:
```	
	./main
```

## Running the project using CMake
Set teminal/command prompt directory to the project folder.

Enter below commands to compile the code:
```
	cmake .
	make
```
To run the program, enter the below command:
```	
	./main
```
## Using the program: 
Follow the instructions displayed to go through the process of performing a transaction with the ATM API.

The correct security pin to proceed with the transaction is 1111. 

Further instructions for using the program will be displayed after entering the pin. An example run is showcased below.

Validity checks have been implemented to ensure only correct information is accepted by the ATM instance.

## Flowchart of the logic implemented:
<img src = "https://github.com/shorane/System_Design_ATM/blob/master/atm_flow.png" height="300"/>

## Example run:

```
Enter 4 digit pin number or enter 0 to exit:
```
User input: 1111	(there are three tries to enter the correct pin, otherwise the session is terminated)
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
User input: 100		(A withdrawal higher than the current balance will result in failure of transaction)
```
Amount before transaction: 599
Amount after transaction: 499
Transaction completed! Would you like to perform another transaction? 
yes/no?
```
User input: no		(if entered yes, the session jumps to account selection and proceeds from there)
```
Thank you for banking with us. Have a nice day!
```

## About the project
The project consists of the 4 following files.

**1. Driver.cpp**
This is the main script of the project and executes the following flow during a transaction.

Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw

- The script first instantiates dummy accounts (whose details are stored in bankAPI.h) and then makes an instance of the class ATM. This simulates card insertion and detection of the user's card serial (here hardcoded to be "1" just as an example). 
- Then the user is asked for the pin by calling the function pinCheck on the instance of the class ATM. As part of the dummy data, the correct pin for the card with serial number 1 is 1111.
- If the pin check is successful (within 3 tries) then the account selection menu is shown.
- Entering a valid account choice leads the user to the transaction menu, where they must select between 3 options, i.e., checking balance, deposit, and withdrawal.

**2. ATM.h**
This script contains the ATM session class and its functions. It accepts commands from Driver.cpp (user inputs) and communicates with the bankAPI which in turn has all the bank records like cardSerial number, name of the user, pin and all the user accounts along with their respective balances.
- Constructor ATM is invoked when card is inserted which creates an instance of type ATM.
- The function pinCheck() is invoked from Driver.cpp which in turn calls pinQuery defined in bankAPI.h and passes card serial number and pin number entered by the user as function arguments. The pinQuery takes the pin input and checks it against pin stored in the bank database for that particular card serial number.
- The program has all the required member functions to allow the driver script to send queries.
- ATM.h just acts as an interface between the user and bankAPI. It never has access to the bank records directly (neither reading nor writing) but can only request modification or account information thus enforcing abstraction and safety of the card holder's data.

**3. cardHolderStruct.h**
It has the structure definition for holding the card holder data. It has the following data members.
- long cardSerial: Serial id of the card which is obtained when the user swipes their card on the ATM machine.
- string name: Name of the card holder.
- int pin: pin for the card.
- unordered_map<long,long> accounts: The map stores account name as the key and it's balance as value for that key. This is implemented in the form of an unordered map as a card holder can have multiple accounts and addition, removal, or finding the account is very fast to compute and easy to implement in the form of unordered_map.
 
**3. bankAPI.h**
This file acts as the central database and also handles all transactions and requests from ATM.h. It has functions that initialize the dummy accounts, checks the input pin obtained from ATM.h against the true pin stored in the database, and display or modify balance in the accounts.
The bankAPI functions are seperated away from the class functions of the ATM class to mimick realistic behavior, where the ATM client just queries the bank server for information, or to make changes to the balance of the card holder. Hence, the bankAPI functionality can be thought of as a bank server.
