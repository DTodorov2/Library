#pragma once
#include <string>
#include <fstream>
#include "../include/User.h"

class Helper 
{
public:
	static User* UserFactory(const std::string& username, const std::string& pass, bool isAdmin);
	static void readUserFromFile(std::ifstream& ifs, std::string& username, std::string& pass, bool& isAdmin);
};
