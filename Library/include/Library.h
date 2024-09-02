#pragma once
#include "User.h"
#include "Book.h"

class Library
{
	std::vector<User*> users;
	std::vector<Book> books;

	int currentUserIndex = -1;

	void login(const std::string& username, const std::string& pass);
	void logout();
};