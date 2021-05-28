#pragma once
#include "Thing.h"
class presMetal :
    public Thing
{
public:
	presMetal(std::string name0, std::string details0, std::string type0, std::string ownerPassport0, double worth0, std::tm buyOutDate0, int purity0, double weight0);
	
	std::string getDetails() const override;

private:

	int purity;
	double weight;
};

