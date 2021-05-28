#include<iostream>
#include<vector>
#include<ctime>
#include "HelpFunctions.h"
#include "Client.h"
#include "debt.h"
#include "deal.h"
using namespace std;

string Client::Passport() const {
	return passport;
}
const vector<debt>& Client::Debts() const {
	return debts;
}
const vector<deal>& Client::CreditHistory() const {
	return creditHistory;
}

Client::Client(string pass) {
	passport = pass;
}
