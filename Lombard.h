#pragma once
class Client;
class Thing;
class debt;


class Lombard
{
public:
	Lombard(std::string location0);

	Lombard(const Lombard& previous);
	Lombard& operator =(const Lombard& previous);

	debt prepareCredit(Client& borrower, const Thing& thing, double amount);

	static void renew(Thing& thing, debt& debt0);

	void giveCredit(Client& borrower, Thing& thing, debt& prepared);

	void closeLoan(const Thing& thing, bool boughtOut = false);
	void deleteThing(const Thing& thing);

	void putOnAcc(double value);

	static bool clientExist(std::string pass);

	static void registerClient(std::string pass);

	void withdraw(double value);

	double Account() const;

	std::string Location() const;
	const std::vector<Thing>& ThingBase() const;
	
	static const std::vector<Client>& getClientBase;

	static const std::vector<Lombard>& getWeb;

	static Lombard& getLombByIdx(int i);
	Client& getClientByIdx(int i);
	debt& getDebtByIdx(const Client& client, int i);
	Thing& thingByDebt(const debt& debt0);

private:

	std::string location;
	static std::vector<Client> clientBase;
	std::vector<Thing> thingBase;
	double account;
	static std::vector<Lombard> web;
};
