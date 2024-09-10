#pragma once
#include "User.h"

class Client : public User
{
public:
	Client(const std::string& username, const std::string& pass);

	void addUser(std::vector<User*>& users) const override;
	void removeUser(std::vector<User*>& users, const std::string& username) const override;
	void addBook(std::vector<Book>& books, int id) const override;
	void removeBook(std::vector<Book>& books, int id) const override;
	void addKeyWords(std::vector<Book>& books, int id) const override;

};