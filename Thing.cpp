#include<iostream>
#include<string>
#include<ctime>
#include<vector>
#include "HelpFunctions.h"
#include "Thing.h"
using namespace std;

Thing::Thing(string name0, string details0, string type0, string ownerPassport0, double worth0, tm buyOutDate0) {
	details = details0;
	name = name0;
	worth = worth0;
	ownerPassport = ownerPassport0;
	buyOutDate = buyOutDate0;
	category = type0;
}

string Thing::Name() const {
	return name;
}

double Thing::Worth() const {
	return worth;
}

string Thing::OwnerPassport() const {
	return ownerPassport;
}

string Thing::getDetails() const {
	return details;
}

string Thing::Category() const {
	return category;
}

bool Thing::purchasable() const {
	tm t = buyOutDate;

	if ((difftime(time(NULL), mktime(&t)) / (60 * 60 * 24)) / 1 > delay) {
		return true;
	}

	return false;
}

bool Thing::operator == (Thing th) const {

	if (this->name == th.name && this->worth == th.worth && this->ownerPassport == th.ownerPassport && this->buyOutDate == th.buyOutDate) {
		return true;
	}

	return false;
}

void Thing::renew(tm newDate) {
	buyOutDate = newDate;
}
