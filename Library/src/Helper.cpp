#include "../include/Helper.h"
#include "../include/Admin.h"
#include "../include/Client.h"

User* Helper::UserFactory(const std::string& username, const std::string& pass, bool isAdmin)
{
	switch (isAdmin)
	{
	case true:
		return new Admin(username, pass);
	case false:
		return new Client(username, pass);
	default:
		break;
	}
}

void Helper::writeStringToFile(std::ofstream& ofs, const std::string& str)
{
	int strLen = str.size();
	ofs.write((const char*)&strLen, sizeof(strLen));
	ofs.write(str.c_str(), strLen);
}

void Helper::writeSetOfStringToFile(std::ofstream& ofs, const std::set<std::string>& set)
{
	int setLen = set.size();
	ofs.write((const char*)&setLen, sizeof(setLen));
	for (std::set<std::string>::iterator it = set.begin(); it != set.end(); ++it)
	{
		Helper::writeStringToFile(ofs, *it);
	}
}

void Helper::readStringFromFile(std::ifstream& ifs, std::string& str)
{
	int strLen = 0;
	ifs.read((char*)&strLen, sizeof(strLen));
	str.resize(strLen);
	ifs.read(&str[0], strLen);
}

void Helper::readSetOfStringFromFile(std::ifstream& ifs, std::set<std::string>& set)
{
	int setLen = 0;
	ifs.read((char*)&setLen, sizeof(setLen));
	for (size_t i = 0; i < setLen; i++)
	{
		int currWordLen = 0;
		ifs.read((char*)&currWordLen, sizeof(currWordLen));
		std::string currWord(currWordLen, '\0');
		ifs.read(&currWord[0], currWordLen);
		set.insert(currWord);
	}
}

void Helper::readUserFromFile(std::ifstream& ifs, std::string& username, std::string& pass, bool& isAdmin)
{
	readStringFromFile(ifs, username);
	readStringFromFile(ifs, pass);
	ifs.read((char*)&isAdmin, sizeof(isAdmin));
}

