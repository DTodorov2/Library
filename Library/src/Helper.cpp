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