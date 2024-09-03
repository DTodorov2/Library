#include "../include/Admin.h"
#include "../include/Helper.h"
#include <regex>
#include <iostream>

Admin::Admin(const std::string& username, const std::string& pass) : User(username, pass, true) {};

void Admin::validateIsAdmin(bool& isAdmin) const
{
	std::regex answerReg("^(yes|no)$");
	std::cout << "Is the user an admin? - yes/no" << std::endl;
	std::string answer;
	std::getline(std::cin, answer);
	while (!std::regex_match(answer, answerReg))
	{
		std::cout << "The answer must be \"yes\" or \"no\" - ";
		std::getline(std::cin, answer);
	}
	if (answer == "yes")
	{
		isAdmin = true;
	}
	else
	{
		isAdmin = false;
	}
}

bool Admin::addUser(std::vector<User*>& users, const std::string& username, const std::string& pass) const
{
	bool isAdmin;
	validateIsAdmin(isAdmin);
	User* newUser = Helper::UserFactory(username, pass, isAdmin);
	users.push_back(newUser);
}

bool Admin::removeUser(std::vector<User*>& users, const std::string& username) const
{
	size_t usersLen = users.size();
	for (size_t i = 0; i < usersLen; i++)
	{
		if (users[i]->getUsername() == username)
		{
			users.erase(users.begin() + i);
			break;
		}
	}
}

bool Admin::addBook(std::vector<Book>& books) const
{

}

bool Admin::removeBook(std::vector<Book>& books) const
{

}