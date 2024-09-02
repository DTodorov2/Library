#pragma once
#include "User.h"

class Admin : public User
{
public:
	void booksAll(const std::vector<Book>& books) const;
	void booksFind(const std::vector<Book>& books, const std::string& option, const std::string& optionString) const;
	void booksView(const std::vector<Book>& books, int bookId) const;
	void booksSort(const std::vector<Book>& books, const std::string& option, bool isAsc) const;
	bool addUser(std::vector<User*>& users, const std::string& username, const std::string& pass) const;
	bool removeUser(std::vector<User*>& users, const std::string& username) const;
	bool addBook(std::vector<Book>& books) const;
	bool removeBook(std::vector<Book>& books) const;
};