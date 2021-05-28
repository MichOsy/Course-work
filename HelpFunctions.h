#pragma once
const std::vector<std::string> thingTypes{ "Presious metals", "Technics", "Other" };
const std::vector<std::string> metals{ "Platinum", "Gold", "Silver" };

void printTypes(const std::vector<std::string>& v);


double checkInputPos(const char name[]);


int checkInputIdx(int noGreater);



bool is_in(char c, std::vector<char> vec);


bool operator == (std::tm first, std::tm second);