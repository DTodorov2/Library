#pragma once
#include <string>
#include "../include/User.h"

class Helper 
{
public:
	static User* UserFactory(const std::string& username, const std::string& pass, bool isAdmin);
};
