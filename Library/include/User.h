#pragma once
#include <string>
#include "Book.h"

class User
{
	std::string username;
	std::string password;
	bool isAdmin = false;

	void printBook(const Book& book) const;
	void sortBooksTitle(const std::vector<Book>& books, bool ascending);
	void sortBooksAuthor(const std::vector<Book>& books, bool ascending);
	void sortBooksYear(const std::vector<Book>& books, bool ascending);
	void sortBooksRating(const std::vector<Book>& books, bool ascending);

public:
	User() = default;
	User(const std::string& username, const std::string& pass, bool isAdmin);

	const std::string& getUsername() const;
	const std::string& getPass() const;
	bool isAdministrator() const;

	void booksAll(const std::vector<Book>& books) const;
	void booksFind(const std::vector<Book>& books, const std::string& option, const std::string& optionString) const;
	void booksView(const std::vector<Book>& books, int bookId) const;
	void booksSort(const std::vector<Book>& books, const std::string& option, bool isAsc);

	virtual bool addUser(std::vector<User*>& users) const = 0;
	virtual bool removeUser(std::vector<User*>& users, const std::string& username) const = 0;
	virtual bool addBook(std::vector<Book>& books, int id) const = 0;
	virtual bool removeBook(std::vector<Book>& books, int id) const = 0;

	void readFromFile(const std::ifstream& ifs);
	void writeToFile(const std::ofstream& ofs) const;
};
