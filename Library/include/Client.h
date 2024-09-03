#pragma once
#include "User.h"

class Client : public User
{
public:
	Client(const std::string& username, const std::string& pass);

	bool addUser(std::vector<User*>& users, const std::string& username, const std::string& pass) const override;
	bool removeUser(std::vector<User*>& users, const std::string& username) const override;
	bool addBook(std::vector<Book>& books) const override;
	bool removeBook(std::vector<Book>& books) const override;
};