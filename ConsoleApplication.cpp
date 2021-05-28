#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<ctime>
#include<map>
#include<set>
#include<conio.h>
#include "HelpFunctions.h"
#include "Lombard.h"
#include "debt.h"
#include "deal.h"
#include "Client.h"
#include "Thing.h"
#include "presMetal.h"
#include "Technics.h"
#include "ConsoleApplication.h"
using namespace std;


void ConsoleApplication::lombardsMenu() {

	if (Lombard::getWeb.size() == 0) {

		bool back = false;
		while (!back) {

			vector<char> buttons{ 'r', 'b' };
			if (Lombard::getWeb.size() == 0) {
				cout << "There's no lombards registered.\n\n";
			}
			else {
				cout << setw(4) << "N." << setw(12) << "Account" << setw(20) << "Location" << '\n';
				for (unsigned i = 0; i < Lombard::getWeb.size(); i++) {
					cout << setw(4) << i + 1 << setw(12) << Lombard::getWeb[i].Account() << " " << setw(19) << Lombard::getWeb[i].Location() << '\n';
				}
				cout << "\n[c] Choose lombard from the list.\n";
				buttons.push_back('c');
			}

			cout << "[r] Register new lombard.\n";
			cout << "[b] Back.\n\n";


			char choice = _getch();
			while (!is_in(choice, buttons)) {
				choice = _getch();
			}
			try {
				switch (choice) {

				case 'r':
					registerNew();
					break;

				case 'b':
					back = true;
					break;

				case 'c':
					int i;
					cout << "Enter lombard's number: ";
					cin >> i;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(32767, '\n');
						cout << "Incorrect input. \n";
					}

					else if (i < 1 || i > Lombard::getWeb.size()) {

						cout << "Lombard with this number doesn't exist.\n";
					}

					else {
						system("cls");
						lombardUse(Lombard::getLombByIdx(i - 1));
					}
					break;

				}
			}
			catch (exception& exc) {
				cerr << "Error: " << exc.what() << ". Try again. \n";
				system("pause");
			}

			system("pause");
			system("cls");
		}
	}
}

void ConsoleApplication::lombardUse(Lombard& lombard) {
	bool back = false;
	while (!back) {
		system("cls");
		vector<char> buttons{ 't', 'c', 'w', 'p', 'b' };

		cout << "Account: " << lombard.Account() << " usd" << '\n';
		cout << "Things number: " << lombard.ThingBase().size() << '\n';
		cout << "Location: " << lombard.Location() << "\n\n";
		cout << "[t] Open things list.\n";
		cout << "[c] Client menu.\n";
		cout << "[w] Withdraw money from the account.\n";
		cout << "[p] Put money on the account.\n";
		cout << "[b] Back.\n";


		char choice = _getch();
		while (!is_in(choice, buttons)) {
			choice = _getch();
		}
		try {
			switch (choice) {

			case 't':
				openThingsList(lombard.ThingBase(), lombard);
				break;

			case 'c':
				passProcessingMenu(lombard);
				break;

			case 'w':
				cout << "Enter amount of money: ";
				double amount;
				cin >> amount;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(32767, '\n');
					cout << "Incorrect input. \n";
					system("pause");
				}


				if (amount < 0) {
					cout << "You can't withdraw negative value. \n";
					system("pause");
				}
				else if (amount > lombard.Account()) {
					cout << "Not enough currency on the account. \n";
					system("pause");
				}
				else {
					lombard.withdraw(amount);
				}
				break;



			case 'p':
				cout << "Enter amount of money: ";
				cin >> amount;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(32767, '\n');
					cout << "Incorrect input. \n";
					system("pause");
				}

				else if (amount < 0) {
					cout << "You can't put negative value. \n";
					system("pause");
				}

				else {
					lombard.putOnAcc(amount);
				}

				break;



			case 'b':
				back = true;
				break;
			}
		}
		catch (exception& exc) {
			cerr << "Error: " << exc.what() << ". Try again. \n";
			system("pause");
		}

	}
}
void ConsoleApplication::passProcessingMenu(Lombard& lombard) {
	cout << "Enter passport: ";
	string pass;


	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, pass);


	int i;
	if (!Lombard::clientExist(pass)) {
		Lombard::registerClient(pass);


		cout << "New client is registered successfully. \n";
		system("pause");

		i = Lombard::getClientBase.size() - 1;
	}
	else {
		for (int k = 0; k < Lombard::getClientBase.size(); k++) {
			if (Lombard::getClientBase[k].Passport() == pass) {
				i = k;
				break;
			}

			if (k == Lombard::getClientBase.size() - 1) {
				throw runtime_error("Client not found");
			}
		}
	}


	ClientMenu(lombard.getClientByIdx(i), lombard);
}
void ConsoleApplication::ClientMenu(Client& client, Lombard& lombard) {
	bool back = false;
	while (!back) {

		system("cls");
		vector<char> buttons{ 'h', 'd', 'c', 'b' };


		cout << "Number of deals in past: " << client.CreditHistory().size() << '\n';
		cout << "Current debts: " << client.Debts().size() << '\n';
		cout << "Passport: " << client.Passport() << "\n\n";
		cout << "[h] Credit history.\n";
		cout << "[d] Current debts.\n";
		cout << "[c] Take credit.\n";
		cout << "[b] Back.\n";


		char choice = _getch();
		while (!is_in(choice, buttons)) {
			choice = _getch();
		}
		try {
			switch (choice) {
			case 'h':
				showCreditHistory(client);
				break;

			case 'd':
				showDebts(client, lombard);
				break;

			case 'c':
				givingCredit(client, lombard);
				break;

			case 'b':
				back = true;
				break;

			}
		}

		catch (exception& exc) {
			cerr << "Error: " << exc.what() << ". Try again. \n";
			system("pause");
		}
	}
}
void ConsoleApplication::showDebts(const Client& client, Lombard& lombard) {
	bool back = false;
	while (!back) {
		system("cls");
		vector<char> buttons{ 'b' };



		if (client.Debts().size() == 0) {
			cout << "No current debts exist. \n\n";
		}
		else {
			cout << setw(6) << "N." << setw(20) << "Thing's name" << setw(20) << "Opening date"
				<< setw(20) << "Last date" << setw(20) << "Current amount" << setw(16) << "Percent per day" << '\n';
			for (int i = 0; i < client.Debts().size(); i++) {
				cout << setw(6) << i + 1 << setw(20) << client.Debts()[i].DealObj() << setw(20)
					<< to_string(client.Debts()[i].StartDebt().tm_mday) + '.' + to_string(client.Debts()[i].StartDebt().tm_mon + 1) + '.' + to_string(client.Debts()[i].StartDebt().tm_year + 1900)
					<< setw(20) << to_string(client.Debts()[i].LastDebt().tm_mday) + '.' + to_string(client.Debts()[i].LastDebt().tm_mon + 1) + '.' + to_string(client.Debts()[i].LastDebt().tm_year + 1900)
					<< setw(20) << client.Debts()[i].currentAmount() << setw(16) << client.Debts()[i].PercentPerDay() << '\n';
			}

			cout << '\n';


			cout << "[c] Close a loan.\n";
			cout << "[r] Renew a loan.\n";

			buttons.push_back('r');
			buttons.push_back('c');
		}

		cout << "[b] Back.\n";


		char choice = _getch();
		while (!is_in(choice, buttons)) {
			choice = _getch();
		}

		try {
			switch (choice) {
			case 'r':
			{
				cout << "Enter number of debt to renew: ";
				int idx = checkInputIdx(client.Debts().size());
				cout << "Renew for " << client.Debts()[idx - 1].renewCost() << "?\n"
					<< "[y] yes\n" << "[n] no\n";
				char agree = _getch();
				while (!is_in(agree, { 'y', 'n' })) {
					agree = _getch();
				}
				if (agree == 'y') {
					lombard.putOnAcc(client.Debts()[idx - 1].renewCost());
					lombard.renew(lombard.thingByDebt(lombard.getDebtByIdx(client, idx - 1)), lombard.getDebtByIdx(client, idx - 1));
					cout << "Credit was successfully renewed. \n";
					system("pause");
				}
				break;
			}


			case 'c':
			{
				cout << "Enter number of debt to close: ";
				int idx = checkInputIdx(client.Debts().size());
				cout << "Close for " << client.Debts()[idx - 1].currentAmount() << "?\n"
					<< "[y] yes\n" << "[n] no\n";
				char agree = _getch();
				while (!is_in(agree, { 'y', 'n' })) {
					agree = _getch();
				}
				if (agree == 'y') {
					lombard.putOnAcc(client.Debts()[idx - 1].currentAmount());
					lombard.closeLoan(lombard.thingByDebt(lombard.getDebtByIdx(client, idx - 1)), true);
					cout << "Credit was successfully closed. \n";
					system("pause");
				}
				break;
			}


			case 'b':
				back = true;
				break;
			}
		}
		catch (exception& exc) {
			cerr << "Error: " << exc.what() << ". Try again. \n";
			system("pause");
		}
	}
}
void ConsoleApplication::givingCredit(Client& client, Lombard& lombard) {
	string name, details, type, brand;
	double worth, weight, desired;
	int purity, manufactureYear;


	cout << "Enter thing's name: ";
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, name);


	cout << "Enter thing's worth(usd): ";
	cin >> worth;
	while (cin.fail() || worth < 0) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Incorrect input. Enter again: ";
		cin >> worth;
	}



	cout << "Choose thing's category from the list below.\n";
	printTypes(thingTypes);
	int choice = checkInputIdx(thingTypes.size());;
	choice--;
	type = thingTypes[choice];


	switch (choice) {
	case 0:
		cout << "Choose metal from the list below.\n";
		printTypes(metals);
		type += '(' + metals[checkInputIdx(metals.size()) - 1] + ')';
		purity = checkInputPos("purity");
		weight = checkInputPos("weight(g)");
		break;


	case 1:
	{
		cout << "Enter production year: ";
		cin >> manufactureYear;
		time_t t = time(0);
		tm now;
		localtime_s(&now, &t);
		while (cin.fail() || manufactureYear < 1900 || manufactureYear > now.tm_year + 1900) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Incorrect input. Enter again: ";
			cin >> manufactureYear;
		}
		cout << "Enter brand: ";
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		getline(cin, brand);

		break;
	}


	default:
		cout << "Enter type: ";
		string tempType;
		cin >> tempType;
		type += '(' + tempType + ')';

		break;
	}


	cout << "Enter some other details about thing(not required): ";
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, details);


	desired = checkInputPos("desired amount of money");
	tm now;
	time_t t = time(0);
	localtime_s(&now, &t);
	Thing item(name, details, type, client.Passport(), worth, now);


	if (choice == 0) {
		item = presMetal(name, details, type, client.Passport(), worth, now, purity, weight);
	}
	else if (choice == 1) {
		item = Technics(name, details, type, client.Passport(), worth, now, manufactureYear, brand);
	}
	debt prepared = lombard.prepareCredit(client, item, desired);



	cout << "Take a loan of " << prepared.Amount() << " usd, with " << prepared.PercentPerDay() << "% rate per day until "
		<< to_string(prepared.LastDebt().tm_mday) + '.' + to_string(prepared.LastDebt().tm_mon + 1) + '.' + to_string(prepared.LastDebt().tm_year + 1900) << " ?\n"
		<< "[y] yes\n" << "[n] no\n";

	char agree = _getch();

	while (!is_in(agree, { 'y', 'n' })) {
		agree = _getch();
	}
	if (agree == 'y') {

		lombard.giveCredit(client, item, prepared);

		cout << "A loan was taken out successfully. \n";
		system("pause");
	}
	else {


		cout << "Loan was declined. \n";
		system("pause");
	}
}
void ConsoleApplication::showCreditHistory(const Client& client) {

	system("cls");

	if (client.CreditHistory().size() == 0) {
		cout << "Credit history is empty. \n\n";
	}
	else {
		cout << setw(14) << "Credit value" << setw(20) << "Thing's name" << setw(14) << "Opening date"
			<< setw(14) << "Closing date" << setw(30) << "Was bought out by the client" << '\n';

		for (const auto& credit : client.CreditHistory()) {
			cout << setw(14) << credit.CreditValue() << setw(20) << credit.DealObj() << setw(14)
				<< to_string(credit.Start().tm_mday) + '.' + to_string(credit.Start().tm_mon + 1) + '.' + to_string(credit.Start().tm_year + 1900)
				<< setw(14) << to_string(credit.End().tm_mday) + '.' + to_string(credit.End().tm_mon + 1) + '.' + to_string(credit.End().tm_year + 1900)
				<< setw(30) << (credit.BoughtOut() ? "yes" : "no") << '\n';
		}
		cout << '\n';
	}

	cout << "[b] Back. \n";


	char choice = _getch();
	while (choice != 'b') {
		choice = _getch();
	}

}
void ConsoleApplication::openThingsList(const vector<Thing>& thingBase, Lombard& lombard) {

	bool back = false;
	while (!back) {
		system("cls");
		vector<char> buttons{ 'b' };


		if (thingBase.size() == 0) {
			cout << "List of things is empty.\n\n";
		}
		else {
			cout << setw(6) << "N." << setw(20) << "Name of thing" << setw(16) << "Thing's worth" << setw(14) << "Purchasable" << '\n';
			for (int i = 0; i < thingBase.size(); i++) {
				cout << setw(6) << i + 1 << setw(20) << thingBase[i].Name() << setw(16) << thingBase[i].Worth() << setw(14) << (thingBase[i].purchasable() ? "yes" : "no") << '\n';
			}
			cout << '\n';
			cout << "[d] More details about a thing.\n";
			cout << "[p] Purchase a thing.\n";
			buttons.push_back('d');
			buttons.push_back('p');
		}
		cout << "[b] Back.\n\n";



		char choice = _getch();
		while (!is_in(choice, buttons)) {
			choice = _getch();
		}
		try {
			switch (choice) {
			case 'd':
				cout << "Enter number of thing to get more details about: ";

				cout << thingBase[checkInputIdx(thingBase.size()) - 1].getDetails();
				cout << '\n';
				system("pause");
				break;

			case 'p':
			{
				cout << "Enter number of thing to purchase: ";
				int i = checkInputIdx(thingBase.size());
				if (thingBase[i - 1].purchasable()) {
					cout << "Purchase " << thingBase[i - 1].Name() << " for " << thingBase[i - 1].Worth() << " usd ?\n[y] yes\n[n] no\n\n";
					choice = _getch();
					while (!is_in(choice, { 'y', 'n' })) {
						choice = _getch();
					}
					if (choice == 'y') {
						lombard.closeLoan(thingBase[i - 1]);
						lombard.putOnAcc(thingBase[i - 1].Worth());
						system("pause");
					}
				}
				else {
					cout << "This thing isn't purchasable now. \n";
					system("pause");
				}
				break;
			}

			case 'b':
				back = true;
				break;
			}
		}
		catch (exception& exc) {
			cerr << "Error: " << exc.what() << ". Try again. \n";
			system("pause");
		}
	}
}

void ConsoleApplication::registerNew() {

	cout << "Enter new lombard's location: ";
	string loc;
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, loc);


	Lombard t{ loc };
	cout << "New lombard at " << loc << " was registered successfully.\n";
}
