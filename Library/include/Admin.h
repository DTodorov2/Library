#pragma once
#include "User.h"

class Admin : public User
{
	void validateIsAdmin(bool& isAdmin) const;
	void validateBookTitleAuthor(std::string& criteria, const std::string& which) const;
	void validateUsername(std::vector<User*>& users, std::string& username) const;
	void validatePass(std::string& pass) const;
	//kak da validiram genre -> dali da napravq set ot vuzmojni janrove i da proverqvam dali e vutre?
	void validatePubYearRating(size_t& num, const std::string& which) const;
	int findFirstEmptyIndex(const std::vector<Book>& books) const;
	bool isItUnique(std::vector<User*>& users, const std::string& username) const;
	
public:
	Admin(const std::string& username, const std::string& pass);

	bool addUser(std::vector<User*>& users) const override;
	bool removeUser(std::vector<User*>& users, const std::string& username) const override;
	bool addBook(std::vector<Book>& books, int id) const override;
	bool removeBook(std::vector<Book>& books, int id) const override;
};