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
	void validateKeyWord(std::string& word) const;
	bool isItUnique(std::vector<User*>& users, const std::string& username) const;
	
public:
	Admin(const std::string& username, const std::string& pass);

	void addUser(std::vector<User*>& users) const override;
	void removeUser(std::vector<User*>& users, const std::string& username) const override;
	void addBook(std::vector<Book>& books, int id) const override;
	void removeBook(std::vector<Book>& books, int id) const override;
	void addKeyWords(std::vector<Book>& books, int id) const override;
};