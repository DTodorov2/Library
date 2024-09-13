#pragma once
#include "User.h"

class Admin : public User
{
	void validateIsAdmin(bool& isAdmin) const;
	void validateTitleAuthorGenre(std::string& criteria, const std::string& which) const;
	void validateUsername(std::vector<User*>& users, std::string& username) const;
	void validatePass(std::string& pass) const;
	void validatePubYear(int& num) const;
	void validateKeyWord(std::string& word) const;
	void validateDesc(std::string& desc) const;
	bool isItUnique(std::vector<User*>& users, const std::string& username) const;
	void swapBooks(Book& b1, Book& b2) const;
	int findFirstEmptyIndex(std::vector<Book>& books) const;

public:
	Admin(const std::string& username, const std::string& pass);

	void addUser(std::vector<User*>& users) const override;
	void removeUser(std::vector<User*>& users, const std::string& username) const override;
	void addBook(std::vector<Book>& books, int& counter) const override;
	void removeBook(std::vector<Book>& books, int id, int& counter) const override;
	void addKeyWords(std::vector<Book>& books, int id) const override;
	void rateBook(std::vector<Book>& books, int id) const override;
	void addDesc(std::vector<Book>& books, int id) const override;
};