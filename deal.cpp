#include<iostream>
#include<vector>
#include<ctime>
#include "HelpFunctions.h"
#include "deal.h"
using namespace std;



double deal::CreditValue() const {
	return creditValue;
}


tm deal::Start() const {
	return start;
}


tm deal::End() const {
	return end;
}


bool deal::BoughtOut() const {
	return boughtOut;
}


string deal::DealObj() const {
	return dealObj;
}


deal::deal(double creditValue0, tm start0, string thingName, bool boughtOut0) {
	boughtOut = boughtOut0;
	creditValue = creditValue0;
	start = start0;
	dealObj = thingName;


	time_t now = time(0);
	localtime_s(&end, &now);
}
