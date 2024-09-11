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

void Helper::readUserFromFile(std::ifstream& ifs, std::string& username, std::string& pass, bool& isAdmin)
{
	int usernameLen = 0;
	ifs.read((char*)&usernameLen, sizeof(usernameLen));
	username.resize(usernameLen);
	ifs.read(&username[0], usernameLen);
	int passLen = 0;
	ifs.read((char*)&passLen, sizeof(passLen));
	pass.resize(passLen);
	ifs.read(&pass[0], passLen);
	ifs.read((char*)&isAdmin, sizeof(isAdmin));
}