#include <iostream>
#include <cstring>
using namespace std;
class Helper{
public:
	int _choice;
	int menuChoice, choice;
	Helper() {
		_choice = 0;
		menuChoice = 0; choice = 0;
	}
	int choice_Function() {
		cout << "\nEnter your choice \n1-)Enter again.. \n2-)Main menu\n0-)Exit\n";
		cin >> choice;
		switch (choice) {
		case 0:
			exit(0);
			break;
		case 1:
			choice = 1;
			break;
		case 2:
			choice = 2;
			break;
		default:
			cout << "Invalid Choice!\n";
			choice_Function();
		}
		return choice;
	}
	int _choiceFunction() {
		cout << "\nEnter your choice \n1-)Main Menu\n0-)Exit\n";
		cin >> _choice;
		switch (_choice) {
		case 0:
			exit(0);
			break;
		case 1:
			_choice = 1;
			break;
		default:
			cout << "Invalid Choice!\n";
			_choiceFunction();
			break;
		}
		return _choice;
	}
	bool authChoiceFunction() {
		cout << "\nEnter your choice \n1-)Enter Again...\n0-)Exit\n";
		cin >> _choice;
		switch (_choice) {
		case 0:
			exit(0);
			break;
		case 1:
			_choice = 1;
			break;
		default:
			cout << "Invalid Choice!\n";
			authChoiceFunction();
		}
		return _choice;
	}
	virtual void menu() = 0;
};

class User: public Helper{
public:
	string name, userName, fName, CNIC, enteredName;
	bool isUser, isAuthroized;
	int PIN, enteredPIN;
	User() {
		name.clear();
		userName.clear();
		fName.clear();
		CNIC.clear();
		enteredName.clear();
		PIN = 0; enteredPIN = 0;
		isAuthroized = 0; isUser = 0;
	}
	
	void setName(string uName) {
		enteredName = uName;
	}
	void setPass(int pin) {
		enteredPIN = pin;
	}
	bool AuthUser() {
		if (userName == enteredName) {
			isUser = true;
		}
		else {
			isUser = false;
		}
		return isUser;
	}
	bool AuthPassword() {
		if (PIN == enteredPIN) {
			isAuthroized = 1;
		}
		else {
			isAuthroized = 0;
		}
		return isAuthroized;
	}
	void AccountInfo() {
		do {
			cout << "Enter your PIN to See you Account Information: \n";
			cin >> enteredPIN;
			if (AuthPassword()) {
				cout << "UserName: "<<userName<<endl;
				cout << "Name: " << name << "\t\t" << "SurName: " << fName<<endl;
				cout << "CNIC: "<<CNIC <<"\t\t";
				if (_choiceFunction() == 1) { menu();}
				break;
			}
			else {
				cout << "Wrong Password!";
				choice_Function();
				if (choice == 2) {
					menu();
					break;
				}
			}
		} while (choice == 1);
	}
};

class Account:public User{
public:
	long accNo;
	int Balance;
	bool availbility;
	Account() { accNo = 0; Balance = 0; availbility = 0; }
	bool checkBlnceAvalibilty(int amount) {
		if (amount <= Balance) { availbility = 1; }
		else { availbility = 0; }
		return availbility;
	}
	void BalanceInquiry() {
		do {
			cout << "Enter you PIN for Balance Inquiry: ";
			cin >> enteredPIN;
			if (AuthPassword()) {
				cout << "Your Current Balance is: " << Balance;
				if (_choiceFunction() == 1) { menu(); }
				break;
			}
			else {
				cout << "Wrong Password!";
				choice_Function();
				if (choice == 2) {
					menu();
					break;
				}
			}
		} while (choice == 1);
	}
};

class Transactions:public Account{
public:
	const string _cashWthdrw = "Cash Withdraw";
	const string _billPymnt = "Bill Payment";
	const string _bnkTrnsfr = "Bank Transfer";
	const string _cashDepsit = "Cash Deposit";
	Transactions() { amnt = 0; }
	int amnt = 0;
	void menu() {
		cout << "\n1-)Cash Withdraw \t\t\t 2-)Fast Cash\n";
		cout << "3-)Bill Payments \t\t\t 4-)Bank Transfer\n";
		cout << "5-)Cash Deposit \t\t\t 6-)Balance Inquiry\n";
		cout << "7-)Account Info  \t\t\t 8-)EXIT\n";
		cout << "\nEnter your choice: ";
		cin >> menuChoice;
		switch (menuChoice)
		{
		case 1:
			CashWithdraw();
			break;
		case 2:
			FastCash();
			break;
		case 3:
			PayBill();
			break;
		case 4:
			BankTransfer();
			break;
		case 5:
			CashDeposit();
			break;
		case 6:
			BalanceInquiry();
			break;
		case 7:
			AccountInfo();
			break;
		case 8:
			exit(0);
		default:
			cout << "Invalid Choice!";
			menu();
		}
	}
	void confirmTransaction(string event, int amount) {
		do {
			cout << "Enter your PIN to confirm this Transaction: ";
			cin >> enteredPIN;
			if (AuthPassword()) { generateReciept(event, amount); break; }
			else {
				cout << "Wrong PIN!\n";
				choice_Function();
				if (choice == 2) {
					menu();
					break;
				}
			}
		} while (choice == 1);
	}
	void CashWithdraw() {
		amnt = 0;
		cout << "Enter amount you want to Withdraw: ";
		cin >> amnt;
		if (checkBlnceAvalibilty(amnt)) {
			confirmTransaction(_cashWthdrw, amnt);
		}
		else {
			cout << "You don't have sufficient Balance in your Account!\n";
			choice_Function();
			if (choice==1) { CashWithdraw(); }
			else if (choice == 2) { menu(); }
		}
	}
	void FastCash() {
		amnt = 0;
		int fChoice = 0;
		cout << "Choose an option to withdraw the Amount: \n";
		cout << "1-)1000 \t\t\t 2-) 2000\n";
		cout << "3-)5000 \t\t\t 4-) 10000\n";
		cout << "5-)20000\t\t\t 6-) 50000\n";
		cout << "7-)Main Menu\n";
		cin >> fChoice;
		switch (fChoice)
		{
		case 1:
			amnt = 1000;
			if (checkBlnceAvalibilty(amnt)) {
				confirmTransaction(_cashWthdrw, amnt);
			}
			else {
				cout << "You don't  have sufficient Balance in your Account!\n";
				choice_Function();
				if (choice == 1) { FastCash(); }
				else if (choice == 2) { menu(); }
			}
			break;
		case 2:
			amnt = 2000;
			if (checkBlnceAvalibilty(amnt)) {
				confirmTransaction(_cashWthdrw, amnt);
			}
			else {
				cout << "You don't  have sufficient Balance in your Account!\n";
				choice_Function();
				if (choice==1) { FastCash(); }
				else if (choice == 2) { menu(); }
			}
			break;
		case 3:
			amnt = 5000;
			if (checkBlnceAvalibilty(amnt)) {
				confirmTransaction(_cashWthdrw, amnt);
			}
			else {
				cout << "You don't  have sufficient Balance in your Account!\n";
				choice_Function();
				if (choice==1) { FastCash(); }
				else if (choice == 2) { menu(); }
			}
			break;
		case 4:
			amnt = 10000;
			if (checkBlnceAvalibilty(amnt)) {
				confirmTransaction(_cashWthdrw, amnt);
			}
			else {
				cout << "You don't  have sufficient Balance in your Account!\n";
				choice_Function();
				if (choice==1) { FastCash(); }
				else if (choice == 2) { menu(); }
			}
			break;
		case 5:
			amnt = 20000;
			if (checkBlnceAvalibilty(amnt)) {
				confirmTransaction(_cashWthdrw, amnt);
			}
			else {
				cout << "You don't  have sufficient Balance in your Account!\n";
				choice_Function();
				if (choice==1) { FastCash(); }
				else if (choice == 2) { menu(); }
			}
			break;
		case 6:
			amnt = 50000;
			if (checkBlnceAvalibilty(amnt)) {
				confirmTransaction(_cashWthdrw, amnt);
			}
			else {
				cout << "You don't  have sufficient Balance in your Account!\n";
				choice_Function();
				if (choice==1) { FastCash(); }
				else if (choice == 2) { menu(); }
			}
			break;
		case 7:
			menu();
			break;
		default:
			cout << "Invalid Choice!\n";
			FastCash();
		}

	}
	void PayBill() {
		amnt = 0;
		string bill;
		cout << "Enter the Bill reference Number / Bill ID/ AccountID to pay bill: ";
		cin >> bill;
		cout << "Enter bill amount: ";
		cin >> amnt;
		if (checkBlnceAvalibilty(amnt)) {
			confirmTransaction(_billPymnt, amnt);
		}
		else {
			cout << "You don't  have sufficient Balance in your Account!\n";
			if (choice_Function() == 1) { PayBill(); }
			else if (choice_Function() == 2) { menu(); }
		}

	}
	void BankTransfer(){
		int cnfirm;
		string bnkName;
		long beni_AccNo;
		amnt = 0;
		cout << "\nEnter Bank Name to transfer the amount: \n";
		cin >> bnkName;
		cout << "Enter Account number of beneficary: \n";
		cin >> beni_AccNo;
		cout << "Enter ammount to transfer: \n";
		cin >> amnt;
		cout << "Please confirm this transaction: \nEnter 1 for yes 0 for No.";
		cin >> cnfirm;
		if (cnfirm ==1) {
			if (checkBlnceAvalibilty(amnt)) {
				confirmTransaction(_bnkTrnsfr, amnt);
			}
			else {
				cout << "You don't  have sufficient Balance in your Account!\n";
				choice_Function();
				if (choice== 1) { BankTransfer(); }
				else if (choice== 2) { menu(); }
			}
		}
		else {
			cout << "Transaction has been cancelled!\n";
			_choiceFunction();
			if (_choice == 1) { menu();}
		}
	}
	void CashDeposit() {
		cout << "Enter amount to Deposit in your Account: ";
		cin >> amnt;
		generateReciept(_cashDepsit, amnt, 1);
	}
	void generateReciept(string TransactionEvent, int amount) {
		cout << "\n\t\t***********RECEIPT***********\n";
		cout << "\n\t\tAccount no: " << accNo<<"\n";
		cout << "\t\tTransaction Type: " << TransactionEvent <<"\n";
		cout << "\t\tAmount Debit: " << amount<<"\n";
		Balance = Balance - amount;
		cout << "\t\tCurrent Balance: " << Balance<<"\n";
		cout << "\t\tThanks! " << name << "\n\t\tHave a nice day!\n"<<"\n";
		cout << "\t\t*****************************\n";
		if (_choiceFunction() ==1) { menu();}
	}
	void generateReciept(string TransactionEvent, int amount, bool isDeposit) {
		cout << "\n\t\t***********RECEIPT***********\n";
		cout << "\n\t\tAccount no: " << accNo << endl;
		cout << "\t\tTransaction Type: " << TransactionEvent <<"\n";
		cout << "\t\tAmount Credit: " << amount<<"\n";
		Balance = Balance + amount;
		cout << "\t\tCurrent Balance: " << Balance<<"\n";
		cout << "\t\tThanks! " << name << "\n\t\tHave a nice day!\n"<<"\n";
		cout << "\t\t*****************************\n";
		if (_choiceFunction()==1) { menu(); }
	}
};


int main()
{
	const int regUser = 3;
	char uName[100];
	string test;
	int pin = 0, i = 0;
	Transactions trans[regUser];

	trans[0].userName = "qadoos01";
	trans[0].PIN = 4040;
	trans[0].name = "Abdul Qadoos";
	trans[0].fName = "Javed";
	trans[0].accNo = 798451546;
	trans[0].Balance = 80000;
	trans[0].CNIC = "26003-0026003-1";

	trans[1].userName = "saad_oxo";
	trans[1].PIN = 1234;
	trans[1].name = "Saad Tahir";
	trans[1].fName = "Tahir";
	trans[1].accNo = 1235645445;
	trans[1].Balance = 100000;
	trans[1].CNIC = "26096-0026096-2";

	trans[2].userName = "rehan";
	trans[2].PIN = 5678;
	trans[2].name = "Muhammad Rehan";
	trans[2].fName = "Akhter";
	trans[2].accNo = 4568791235;
	trans[2].Balance = 90000;
	trans[2].CNIC = "35202-0000085-2";
	do 
	{
		i = 0;
		cout << "Enter UserName: ";
		cin >> uName;
		for (int i = 0; i < strlen(uName); i++) {
			uName[i] = tolower(uName[i]);
		}
		while(i < regUser) {
			trans[i].setName(uName);
			trans[i].AuthUser();
			if(trans[i].isUser){
				goto EnterPassword;
			}
			i++;
		}
		cout << "User Not Found!\n";
		trans[i].authChoiceFunction();
		
	}while(!trans[i].isUser && trans[i]._choice);

EnterPassword:
	do {
		cout << "Welcome " << trans[i].name << "! \nEnter your 4 Digit PIN: ";
		cin >> pin;
		trans[i].setPass(pin);
		if (trans[i].AuthPassword()) {
			cout << "Succesfully Authorized!\n";;
			trans[i].menu(); break;
		}
		else {
			cout << "Inavlid Credetials!";
			trans[i].authChoiceFunction();
		}
	} while(trans[i]._choice);

	return 0;
}

