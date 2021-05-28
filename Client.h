#pragma once
class deal;
class debt;

class Client
{
public:

	std::string Passport() const;

	const std::vector<debt>& Debts() const;
	const std::vector<deal>& CreditHistory() const;

private:
	Client(std::string pass);

	std::string passport;

	std::vector<debt> debts;
	std::vector<deal> creditHistory;

	friend class Lombard;
};

