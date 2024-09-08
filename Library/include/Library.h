#pragma once
#include "User.h"
#include "Book.h"

class Library
{
	std::vector<User*> users;
	std::vector<Book> books;

	int currentUserIndex = -1;

	bool isItUnique(const std::string& username) const;

	template <typename T>
	void readFromVector(std::vector<T>& vec) const;
	//BIG 6

public:
	void login(const std::string& username, const std::string& pass);
	void logout();
	void open(const std::string& fileName) const; //opens a File
	void close(std::fstream& f) const; // closes a file
	void save(std::fstream& f) const;
	void saveas(std::fstream& f) const;
	void help() const;

	void setCurrentUserIndex(int id);
};