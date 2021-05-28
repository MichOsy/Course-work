#include<iostream>
#include<string>
#include "Technics.h"
using namespace std;

Technics::Technics(string name0, string details0, string type0, string ownerPassport0, double worth0, tm buyOutDate0, int manufactureYear0, string brand0)
	: Thing(name0, details0, type0, ownerPassport0, worth0, buyOutDate0)
{
	brand = brand0;
	manufactureYear = manufactureYear0;
}


string Technics::getDetails() const {
	return "Production year: " + to_string(manufactureYear) + ". \n" + "Producer: " + brand + ". \n" + details;
}
