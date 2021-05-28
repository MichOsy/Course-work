#include<iostream>
#include<string>
#include<ctime>
#include<vector>
#include "Lombard.h"
#include "debt.h"
#include "Client.h"
#include "Thing.h"
#include "deal.h"
using namespace std;

Lombard::Lombard(const Lombard& previous) {
	account = previous.account;
	location = previous.location;
	thingBase = previous.thingBase;
}


Lombard& Lombard::operator =(const Lombard& previous) {
	account = previous.account;
	location = previous.location;
	thingBase = previous.thingBase;
	return *this;
}


Lombard::Lombard(string location0) {
	account = 0;
	location = location0;
	web.push_back(*this);
}


debt Lombard::prepareCredit(Client& borrower, const Thing& thing, double amount) {

	double percentPerDay = 0.5;
	int termInDays = 0;


	if (borrower.creditHistory.size()) {
		int badDeals = 0;
		for (const auto& oneDeal : borrower.creditHistory) {
			if (!oneDeal.BoughtOut()) {
				badDeals++;
			}
		}

		percentPerDay *= (0.5 + (badDeals / borrower.creditHistory.size()));
	}



	if (amount > 0.75 * thing.Worth() / 1) {
		throw runtime_error("Desired amount is too big");
	}


	if (amount < 10) {
		throw runtime_error("Credit amount is too low");
	}
	else if (amount <= 100) {
		termInDays = 7;
	}
	else if (amount <= 1000) {
		termInDays = 30;
	}
	else {
		termInDays = 180;
	}


	return { amount, percentPerDay, termInDays, thing.Name() };
}


void Lombard::renew(Thing& thing, debt& debt0) {
	int termInDays;
	double amount = 0.75 * thing.Worth();


	if (amount <= 100) {
		termInDays = 7;
	}
	else if (amount <= 1000) {
		termInDays = 30;
	}
	else {
		termInDays = 180;
	}


	time_t now = time(0);
	tm startDebt, lastDebt;
	localtime_s(&startDebt, &now);


	now += termInDays * 24 * 60 * 60;
	localtime_s(&lastDebt, &now);


	thing.renew(lastDebt);
	debt0.renew(lastDebt, startDebt);
}


void Lombard::giveCredit(Client& borrower, Thing& thing, debt& prepared) {

	withdraw(prepared.Amount());
	thingBase.push_back(thing);
	borrower.debts.push_back(prepared);
}


void Lombard::closeLoan(const Thing& thing, bool boughtOut) {
	for (auto& borrower : clientBase) {
		if (thing.OwnerPassport() == borrower.passport) {
			for (unsigned int i = 0; i < borrower.debts.size(); i++) {
				if (borrower.debts[i].DealObj() == thing.Name()) {

					deleteThing(thing);
					borrower.creditHistory.push_back({ borrower.debts[i].Amount(), borrower.debts[i].StartDebt(), thing.Name(), boughtOut });
					borrower.debts.erase(borrower.debts.begin() + i);
					return;

				}
			}

			throw runtime_error("Debt not found");
		}
	}

	throw runtime_error("Owner not found");
}


void Lombard::deleteThing(const Thing& thing) {
	for (unsigned int i = 0; i < thingBase.size(); i++) {
		if (thing == thingBase[i]) {

			thingBase.erase(thingBase.begin() + i);
			return;

		}
	}

	throw runtime_error("Thing not found");
}


void Lombard::putOnAcc(double value) {

	if (value < 0) {
		throw runtime_error("Value can't be negative");
	}

	account += value;
}


bool Lombard::clientExist(string pass) {

	for (const auto& client : clientBase) {
		if (client.Passport() == pass) {

			return true;
		}
	}

	return false;
}


void Lombard::registerClient(string pass) {

	if (clientExist(pass)) {
		throw runtime_error("Client already exist");
	}

	clientBase.push_back({ pass });
}


void Lombard::withdraw(double value) {

	if (value < 0) {
		throw runtime_error("Value can't be negative");
	}
	else if (value > account) {
		throw runtime_error("Not enough currency on the account");
	}

	account -= value;
}


double Lombard::Account() const {
	return account;
}


string Lombard::Location() const {
	return location;
}


const vector<Thing>& Lombard::ThingBase() const {
	return thingBase;
}


Lombard& Lombard::getLombByIdx(int i) {
	return web[i];
}


Client& Lombard::getClientByIdx(int i) {
	return clientBase[i];
}


debt& Lombard::getDebtByIdx(const Client& client, int i) {
	for (auto& client1 : clientBase) {
		if (client1.Passport() == client.Passport()) {

			return client1.debts[i];
		}
	}

	throw runtime_error("Client not found");
}


Thing& Lombard::thingByDebt(const debt& debt0) {
	for (int i = 0; i < thingBase.size(); i++) {
		if (thingBase[i].Name() == debt0.DealObj()) {

			return thingBase[i];
		}
	}

	throw runtime_error("Thing not found");
}

vector<Client> Lombard::clientBase;
vector<Lombard> Lombard::web;

const vector<Client>& Lombard::getClientBase = clientBase;
const vector<Lombard>& Lombard::getWeb = web;
