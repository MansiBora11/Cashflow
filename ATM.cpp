#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class Account // class atm
{
private: // private member varibles
	long int account_No;
	string name;
	int PIN;
	double balance;
	string mobile_No;

public: // public member functions
	// setData function is setting the Data into the private member variables
	Account(long int account_No, string name, int PIN, double balance, string mobile_No)
	{
		this->account_No = account_No; // assigning the formal arguments to the private member var's
		this->name = name;
		this->PIN = PIN;
		this->balance = balance;
		this->mobile_No = mobile_No;
	}

	// getAccountNo function is returning the user's account no.
	long int getAccountNo()
	{
		return account_No;
	}

	// getName function is returning the user's Name
	string getName()
	{
		return name;
	}

	// getPIN function is returning the user's PIN
	int getPIN()
	{
		return PIN;
	}

	// getBalance is returning the user's Bank Balance
	double getBalance()
	{
		return balance;
	}

	// getMobileNo is returning the user's Mobile No.
	string getMobileNo()
	{
		return mobile_No;
	}

	// setMobile function is Updating the user mobile no
	void setMobile(string mob_prev, string mob_new)
	{
		if (mob_prev == mobile_No) // it will check old Mobile no
		{
			mobile_No = mob_new; // and Update with new, if old matches
			cout << endl
				 << "Sucessfully Updated Mobile no.";
		}

		else // Does not update if old mobile no. does not matches
		{
			cout << endl
				 << "Incorrect !!! Old Mobile no";
		}
	}

	// cashWithDraw function is used to withdraw money from ATM
	void cashWithDraw(int amount_a)
	{
		if (amount_a > 0 && amount_a < balance) // check entered amount validity
		{
			balance -= amount_a; // balance = balance - amount_a
			cout << endl
				 << "Please Collect Your Cash";
			cout << endl
				 << "Available Balance :" << balance;
		}

		else
		{
			cout << endl
				 << "Invalid Input or Insufficient Balance";
		}
	}

	void cashDeposit(int amount_a)
	{
		if (amount_a > 0) // check entered amount validity
		{
			balance += amount_a; // balance = balance - amount_a
			cout << endl
				 << "Money deposited successfully ";
			cout << endl
				 << "Available Balance :" << balance;
		}

		else
		{
			cout << endl
				 << "Invalid Input or Insufficient Balance";
		}
	}
};

class ATM
{
public:
	vector<Account *> users;

	void addAccount()
	{
		long int account_No = 1000000 + (rand() % 999999);
		string name;
		int PIN;
		double balance = 0;
		string mobile_No;

		cout << "Enter name: ";
		cin >> name;
		cout << "Enter pin: ";
		cin >> PIN;
		cout << "Enter mobile number: ";
		cin >> mobile_No;

		Account *newAcc = new Account(account_No, name, PIN, balance, mobile_No);
		users.push_back(newAcc);
		cout << "New User added with following details:-\n";
		cout << "Name: " << name << endl;
		cout << "Mobile No: " << mobile_No << endl;
		cout << "Account No: " << account_No << endl;
		cout << "Pin: " << PIN << endl;
		cout << "Balance: " << balance << endl;
	}

	void getAllAccounts()
	{
		for (Account *user : users)
			cout << user->getAccountNo() << endl;
	}

	Account *validateAccount(long int account_no, int pin)
	{
		Account *acc = nullptr;
		for (Account *user : users)
		{
			if (user->getAccountNo() == account_no && user->getPIN() == pin)
			{
				acc = user;
				break;
			}
		}
		return acc;
	}
};

int main()
{
	srand(time(0));
	int choice = 0, pin; // enterPIN and enterAccountNo. ---> user authentication
	long int account_no;
	int amount;
	string oldNo, newNo;
	Account *user;

	ATM atm;
	do
	{
		cout << "\n**** Welcome to MDM Bank ****\n";
		cout << "Select Options\n";
		cout << "1. Create New User\n";
		cout << "2. Existing User\n";
		cout << "3. List All Accounts\n";
		cout << "4. Exit\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
			atm.addAccount();
			break;
		case 2:
			cout << "Enter Account No: ";
			cin >> account_no;
			cout << "Enter Pin: ";
			cin >> pin;
			user = atm.validateAccount(account_no, pin);
			if (user)
			{
				do
				{
					cout << "\n**** Welcome " << user->getName() << "****\n";
					cout << endl
						 << "Select Options ";
					cout << endl
						 << "1. Check Balance";
					cout << endl
						 << "2. Cash withdraw";
					cout << endl
						 << "3. Show User Details";
					cout << endl
						 << "4. Update Mobile no.";
					cout << endl
						 << "5. Cash Deposit";
					cout << endl
						 << "6. Exit" << endl;
					cin >> choice;

					switch (choice) // switch condition
					{
					case 1:
						cout << endl
							 << "Your Bank balance is :" << user->getBalance();
						// getBalance is ... printing the users	bank balance

						break;

					case 2:
						cout << endl
							 << "Enter the amount :";
						cin >> amount;
						user->cashWithDraw(amount); // calling cashWithdraw function
													// passing the withdraw amount
						break;

					case 3:
						cout << endl
							 << "*** User Details are :- ";
						cout << endl
							 << "-> Account no :" << user->getAccountNo();
						cout << endl
							 << "-> Name      :" << user->getName();
						cout << endl
							 << "-> Balance   :" << user->getBalance();
						cout << endl
							 << "-> Mobile No. :" << user->getMobileNo();
						// getting and printing user details
						break;

					case 4:
						cout << endl
							 << "Enter Old Mobile No. ";
						cin >> oldNo; // take old mobile no

						cout << endl
							 << "Enter New Mobile No. ";
						cin >> newNo; // take new mobile no

						user->setMobile(oldNo, newNo); // now set new mobile no
						break;

					case 5:
						cout << endl
							 << "Enter the amount :";
						cin >> amount;
						user->cashDeposit(amount); // calling cashWithdraw function
												   // passing the withdraw amount
						break;
					case 6:
						break; // exit application

					default: // handle invalid user inputs
						cout << endl
							 << "Enter Valid Data !!!";
					}
					if (choice==6)
						break;
				} while (1);
			}
			else
			{
				cout << "Invalid Details\n";
			}
			break;
		case 3:
			atm.getAllAccounts();
			break;
		case 4:
			cout << "Thank you for using our ATM";
			return 0;
		default:
			cout << "Invalid input\n";
		}
	} while (1); // condition will always TRUE and loop is										capable of running infinite times

	return 0;
}
