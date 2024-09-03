#pragma once
#include "User.h"
#include "Book.h"

class Library
{
	std::vector<User*> users;
	std::vector<Book> books;

	int currentUserIndex = -1;

public:
	void login(const std::string& username, const std::string& pass);
	void logout();
	void open(const std::string& fileName) const; //opens a File
	void close(/*tuka nqkuv stream priema*/) const; // closes a file
	void save(/*tuka nqkuv stream priema*/) const;
	void saveas(/*tuka nqkuv stream priema*/) const;
	void help() const;
};