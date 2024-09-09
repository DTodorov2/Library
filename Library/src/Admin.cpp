#include "../include/Admin.h"
#include "../include/Helper.h"
#include <regex>
#include <iostream>

Admin::Admin(const std::string& username, const std::string& pass) : User(username, pass, true) {};

void Admin::validateIsAdmin(bool& isAdmin) const
{
	std::regex answerReg("^(yes|no)$");
	std::cout << "Is the user an admin? - yes/no" << std::endl;
	std::string answer;
	std::getline(std::cin, answer);
	while (!std::regex_match(answer, answerReg))
	{
		std::cout << "The answer must be \"yes\" or \"no\" - ";
		std::getline(std::cin, answer);
	}
	if (answer == "yes")
	{
		isAdmin = true;
	}
	else
	{
		isAdmin = false;
	}
}

bool Admin::isItUnique(std::vector<User*>& users, const std::string& username) const
{
	size_t usersLen = users.size();
	for (size_t i = 0; i < usersLen; i++)
	{
		if (users[i]->getUsername() == username)
		{
			return false;
		}
	}
	return true;
}

void Admin::validatePass(std::string& pass) const
{
	std::cout << "Enter password: ";
	std::getline(std::cin, pass);
	while (pass.size() == 0)
	{
		std::cout << "The password must be at least one character!" << std::endl;
		std::cout << "Enter password: ";
		std::getline(std::cin, pass);
	}
}

void Admin::validateUsername(std::vector<User*>& users, std::string& username) const
{
	std::cout << "Enter username: ";
	std::getline(std::cin, username);
	while (username.size() == 0 || !isItUnique(users, username))
	{
		std::cout << "The username must be at least one character!" << std::endl;
		std::cout << "Enter username: ";
		std::getline(std::cin, username);
		std::cout << std::endl;
	}
}

void Admin::addUser(std::vector<User*>& users) const
{
	bool isAdmin;
	std::string username, pass;
	validateIsAdmin(isAdmin);
	validateUsername(users, username);
	validatePass(pass);
	User* newUser = Helper::UserFactory(username, pass, isAdmin);
	users.push_back(newUser);
}

void Admin::removeUser(std::vector<User*>& users, const std::string& username) const
{
	size_t usersLen = users.size();
	for (size_t i = 0; i < usersLen; i++)
	{
		if (users[i]->getUsername() == username)
		{
			users.erase(users.begin() + i);
			break;
		}
	}
}

void Admin::validateBookTitleAuthor(std::string& criteria, const std::string& which) const
{
	std::regex reg("^[a-zA-Z]+$");
	std::cout << "Enter the " << which << " of the book: ";
	std::getline(std::cin, criteria);
	while (!std::regex_match(criteria, reg))
	{
		std::cout << "The " << which << "must contain only letters and have length mre than zero!" << std::endl;
		std::cout << "Your answer: ";
		std::getline(std::cin, criteria);
	}
}

void Admin::validatePubYearRating(size_t& num, const std::string& which) const
{
	std::regex reg("^[0-9]+$");
	std::string numStr;
	std::cout << "Enter the " << which << " of the book: ";
	std::getline(std::cin, numStr);
	while (!std::regex_match(numStr, reg))
	{
		std::cout << "The " << which << " must be greater or equal to zero and have length greater than zero!" << std::endl;
		std::cout << "Your answer: ";
		std::getline(std::cin, numStr);
	}

	num = std::stoull(numStr);
}

void Admin::addBook(std::vector<Book>& books, int id) const
{
	std::string title, author, genre;
	size_t pubYear, rating;

	validateBookTitleAuthor(title, "title");
	validateBookTitleAuthor(author, "author");
	validatePubYearRating(pubYear, "publication year");
	validatePubYearRating(rating, "rating");
	//validate genre

	books.push_back(Book(id, title, author, genre, pubYear, rating));
	std::cout << "The book is added successfully!" << std::endl;
}

void Admin::removeBook(std::vector<Book>& books, int id) const
{
	size_t booksLen = books.size();
	for (size_t i = 0; i < booksLen; i++)
	{
		if (books[i].getId() == id)
		{
			books[i].setId(-1);
			return;
		}
	}
	std::cout << "The book is removed successfully!" << std::endl;
}