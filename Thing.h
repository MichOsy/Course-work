#pragma once
class Thing
{
public:
	Thing(std::string name0, std::string details0, std::string type0, std::string ownerPassport0, double worth0, std::tm buyOutDate0);
	std::string Name() const;
	double Worth() const;
	std::string OwnerPassport() const;
	virtual std::string getDetails() const;
	virtual std::string Category() const;
	bool purchasable() const;
	bool operator == (Thing th) const;
	void renew(std::tm newDate);

protected:

	std::string category = "Other";
	int delay = 1;
	std::string details;
	std::string name;
	double worth;
	std::string ownerPassport;
	std::tm buyOutDate;

};

