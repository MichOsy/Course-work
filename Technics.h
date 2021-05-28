#pragma once
#include "Thing.h"
class Technics :
    public Thing
{
public:
	Technics(std::string name0, std::string details0, std::string type0, std::string ownerPassport0, double worth0, std::tm buyOutDate0, int manufactureYear0, std::string brand0);

	std::string getDetails() const override;

private:

	int manufactureYear;
	std::string brand;
};

