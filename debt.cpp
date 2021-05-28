#include<iostream>
#include<ctime>
#include<string>
#include "debt.h"
using namespace std;

	tm debt::StartDebt() const {
		return startDebt;
	}

	tm debt::LastDebt() const {
		return lastDebt;
	}

	double debt::PercentPerDay() const {
		return percentPerDay;
	}

	double debt::Amount() const {
		return amount;
	}

	string debt::DealObj() const {
		return dealObj;
	}

	double debt::currentAmount() const {
		tm t = startDebt;
		return (int(difftime(time(NULL), mktime(&t)) / (60 * 60 * 24)) * percentPerDay + 1) * amount;
	}

	double debt::renewCost() const {
		tm t = startDebt;
		return (int(difftime(time(NULL), mktime(&t)) / (60 * 60 * 24)) * percentPerDay) * amount;
	}

	debt::debt(double amount0, double percentPerDay0, int termInDays, string dealObj0) {
		time_t now = time(0);
		localtime_s(&startDebt, &now);
		now += termInDays * 24 * 60 * 60;
		localtime_s(&lastDebt, &now);
		amount = amount0;
		percentPerDay = percentPerDay0;
		dealObj = dealObj0;
	}

	void debt::renew(tm newDate, tm now) {
		startDebt = now;
		lastDebt = newDate;
	}
