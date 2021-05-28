#include<iostream>
#include<vector>
#include<ctime>
#include"HelpFunctions.h"
using namespace std;


void printTypes(const vector<string>& v) {
	for (int i = 0; i < v.size(); i++) {
		cout << '[' << i + 1 << ']' << ' ' + v[i] << '\n';
	}
}


double checkInputPos(const char name[]) {
	cout << "Enter " << name << ": ";
	double x;
	cin >> x;
	while (cin.fail() || x < 0) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Incorrect input. Enter again: ";
		cin >> x;
	}
	return x;
}


int checkInputIdx(int noGreater) {
	int x;
	cin >> x;
	while (cin.fail() || x < 1 || x > noGreater) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Incorrect input. Enter again: ";
		cin >> x;
	}
	return x;
}


bool is_in(char c, vector<char> vec) {
	for (const auto& elem : vec) {
		if (c == elem) {
			return true;
		}
	}
	return false;
}


bool operator == (tm first, tm second) {
	if (first.tm_mday == second.tm_mday && first.tm_mon == second.tm_mon && first.tm_year == second.tm_year && first.tm_min == second.tm_min && first.tm_hour == second.tm_hour && first.tm_isdst == second.tm_isdst) {
		return true;
	}
	return false;
}
