#pragma once
#include <string>
#include "Book.h"

class User
{
	std::string username;
	std::string password;
	bool isAdmin = false;

	void printBook(const Book& book) const;
	void sortBooksTitle(std::vector<Book>& books, bool ascending);
	void sortBooksAuthor(std::vector<Book>& books, bool ascending);
	void sortBooksYear(std::vector<Book>& books, bool ascending);
	void sortBooksRating(std::vector<Book>& books, bool ascending);

public:
	User() = default;
	User(const std::string& username, const std::string& pass, bool isAdmin);

	const std::string& getUsername() const;
	const std::string& getPass() const;
	bool isAdministrator() const;

	void booksAll(const std::vector<Book>& books) const;
	void booksFind(const std::vector<Book>& books, const std::string& option, const std::string& optionString) const;
	void booksView(const std::vector<Book>& books, int bookId) const;
	void booksSort(std::vector<Book>& books, const std::string& option, bool isAsc);

	virtual void addUser(std::vector<User*>& users) const = 0;
	virtual void removeUser(std::vector<User*>& users, const std::string& username) const = 0;
	virtual void addBook(std::vector<Book>& books, int id) const = 0;
	virtual void removeBook(std::vector<Book>& books, int id) const = 0;

	void readFromFile(std::ifstream& ifs);
	void writeToFile(std::ofstream& ofs) const;

	virtual ~User() = default;
};
