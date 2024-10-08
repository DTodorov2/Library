#pragma once
#include <string>
#include <fstream>
#include "../include/User.h"

class Helper 
{
public:
	static User* UserFactory(const std::string& username, const std::string& pass, bool isAdmin);
	static void readUserFromFile(std::ifstream& ifs, std::string& username, std::string& pass, bool& isAdmin);
	static void writeStringToFile(std::ofstream& ofs, const std::string& str);
	static void writeSetOfStringToFile(std::ofstream& ofs, const std::set<std::string>& set);
	static void readStringFromFile(std::ifstream& ifs, std::string& str);
	static void readSetOfStringFromFile(std::ifstream& ifs, std::set<std::string>& set);

};
