#include "../include/Admin.h"
#include "../include/Helper.h"
#include <regex>
#include <iostream>
#include <ctime>
#pragma warning(disable:4996)

Admin::Admin(const std::string& username, const std::string& pass) : User(username, pass, true) {};

void Admin::validateIsAdmin(bool& isAdmin) const
{
	std::regex answerReg("^(y|n|yes|no)$");
	std::cout << "Is the user an admin? - yes/no" << std::endl;
	std::string answer;
	std::cout << "Your answer: ";
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
	std::regex reg("^[a-zA-Z\. ]+$");
	std::cout << "Enter the " << which << " of the book: ";
	std::getline(std::cin, criteria);
	while (!std::regex_match(criteria, reg))
	{
		std::cout << "The " << which << "must contain only letters and have length mre than zero!" << std::endl;
		std::cout << "Your answer: ";
		std::getline(std::cin, criteria);
	}
}

void Admin::validatePubYear(size_t& num) const
{
	std::regex reg("^[0-9]+$");
	std::string numStr;
	std::cout << "Enter the publication year of the book: ";
	std::getline(std::cin, numStr);
	std::time_t t = std::time(nullptr);
	std::tm* localTime = std::localtime(&t);
	int currentYear = localTime->tm_year + 1900;
	while (!std::regex_match(numStr, reg))
	{
		std::cout << "The publication year must be greater or equal to zero and have length greater than zero!" << std::endl;
		std::cout << "Your answer: ";
		std::getline(std::cin, numStr);
		num = std::stoull(numStr);
		if (num > currentYear)
		{
			std::cout << "Invalid year!" << std::endl;
			continue;
		}
	}
}

void Admin::addBook(std::vector<Book>& books, int id) const
{
	std::string title, author, genre, ratingStr;
	size_t pubYear, rating;

	validateBookTitleAuthor(title, "title");
	validateBookTitleAuthor(author, "author");
	validatePubYear(pubYear);
	rating = validateRating();
	std::cout << "Enter the genre of the book: ";
	std::getline(std::cin, genre);

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
			books[i].setAvailability(false);
			return;
		}
	}
	std::cout << "The book is removed successfully!" << std::endl;
}

void Admin::validateKeyWord(std::string& word) const
{
	std::regex wordReg("^[a-zA-Z0-9\.\-]+$");
	std::cout << "Enter a key word or \"exit\": ";
	std::getline(std::cin, word);
	while (!std::regex_match(word, wordReg))
	{
		std::cout << "There should not be any spaces and the length must be greater than 0!" << std::endl;
		std::cout << "Enter a keyword or \"exit\": ";
		std::getline(std::cin, word);
	}
}

void Admin::addKeyWords(std::vector<Book>& books, int id) const
{
	std::string currWord;
	while (true)
	{
		validateKeyWord(currWord);
		if (currWord == "exit")
		{
			return;
		}
		books[id].addKeyWord(currWord);
	}
}

void Admin::rateBook(std::vector<Book>& books, int id) const
{
	std::cout << "Sorry, you are not allowed to give rating to books!" << std::endl;
}

void Admin::validateDesc(std::string& desc) const
{
	std::cout << "Enter the description: ";
	std::getline(std::cin, desc);
	while (desc.size() == 0)
	{
		std::cout << "The description must be at least 1 character long!" << std::endl;
		std::cout << "Enter the description: ";
		std::getline(std::cin, desc);
	}
}


void Admin::addDesc(std::vector<Book>& books, int id) const
{
	std::string desc;
	validateDesc(desc);
	books[id].setDesc(desc);
	std::cout << "The descripion is added successfully!" << std::endl;
}
