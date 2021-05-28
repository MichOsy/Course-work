#pragma once
class debt
{
public:
	debt(double amount0, double percentPerDay0, int termInDays, std::string dealObj0);

	tm StartDebt() const;
	tm LastDebt() const;

	double PercentPerDay() const;
	double Amount() const;

	std::string DealObj() const;

	double currentAmount() const;
	double renewCost() const;


	void renew(tm newDate, tm now);

private:
	tm startDebt, lastDebt;
	double amount;
	double percentPerDay;
	std::string dealObj;

};

