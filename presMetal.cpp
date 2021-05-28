#include<iostream>
#include<string>
#include "presMetal.h"
using namespace std;


presMetal::presMetal(string name0, string details0, string type0, string ownerPassport0, double worth0, tm buyOutDate0, int purity0, double weight0)
	: Thing(name0, details0, type0, ownerPassport0, worth0, buyOutDate0)
{
	purity = purity0;
	weight = weight0;
}


string presMetal::getDetails() const{
	return "Purity: " + to_string(purity) + ". \n" + "Weight: " + to_string(weight) + ". \n" + details;
}