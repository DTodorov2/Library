#pragma once
#include <string>
#include "Book.h"

class User
{
	std::string username;
	std::string password;
	bool isAdmin = false;
	void printBook(const Book& book) const;
	void sortBooksTitle(std::vector<Book>& books, bool ascending, int without);
	void sortBooksAuthor(std::vector<Book>& books, bool ascending, int without);
	void sortBooksYear(std::vector<Book>& books, bool ascending, int without);
	void sortBooksRating(std::vector<Book>& books, bool ascending, int without);

protected:
	int validateRating() const;

public:
	User() = default;
	User(const std::string& username, const std::string& pass, bool isAdmin);

	const std::string& getUsername() const;
	const std::string& getPass() const;
	bool isAdministrator() const;

	void booksAll(const std::vector<Book>& books, int counter) const;
	void booksFind(const std::vector<Book>& books, const std::string& option, const std::string& optionString, int counter) const;
	void booksView(const std::vector<Book>& books, int bookId) const;
	void booksSort(std::vector<Book>& books, const std::string& option, bool isAsc, int without);

	virtual void addUser(std::vector<User*>& users) const = 0;
	virtual void removeUser(std::vector<User*>& users, const std::string& username) const = 0;
	virtual void addBook(std::vector<Book>& books, int& id) const = 0;
	virtual void removeBook(std::vector<Book>& books, int id, int& counter) const = 0;
	virtual void addKeyWords(std::vector<Book>& books, int id) const = 0;
	virtual void rateBook(std::vector<Book>& books, int id) const = 0;
	virtual void addDesc(std::vector<Book>& books, int id) const = 0;

	void writeToFile(std::ofstream& ofs) const;

	virtual ~User() = default;
};
