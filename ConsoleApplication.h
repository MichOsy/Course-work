#pragma once
#include<vector>
class Client;
class Lombard;
class Thing;

class ConsoleApplication
{
public:

	static void lombardsMenu();

private:

	static void lombardUse(Lombard& lombard);
	static void passProcessingMenu(Lombard& lombard);
	static void ClientMenu(Client& client, Lombard& lombard);
	static void showDebts(const Client& client, Lombard& lombard);
	static void givingCredit(Client& client, Lombard& lombard);
	static void showCreditHistory(const Client& client);
	static void openThingsList(const std::vector<Thing>& thingBase, Lombard& lombard);
	static void registerNew();
};

