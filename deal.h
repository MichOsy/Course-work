#pragma once
class deal
{
public:
	deal(double creditValue0, tm start0, std::string thingName, bool boughtOut0);
	double CreditValue() const;
	tm Start() const;
	tm End() const;
	bool BoughtOut() const;
	std::string DealObj() const;
private:

	double creditValue;
	tm start;
	tm end;
	std::string dealObj;
	bool boughtOut;
};

