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
			std::cout << "This username is already taken!" << std::endl;
			return false;
		}
	}
	return true;
}

void Admin::validatePass(std::string& pass) const
{
	std::regex passReg("^[^ ][a-zA-Z0-9\\.\\- ]+$");
	std::cout << "Enter password: ";
	std::getline(std::cin, pass);
	while (!std::regex_match(pass.c_str(), passReg))
	{
		std::cout << "The password must be at least one character!" << std::endl;
		std::cout << "Enter password: ";
		std::getline(std::cin, pass);
	}
}

void Admin::validateUsername(std::vector<User*>& users, std::string& username) const
{
	std::regex usernameReg("^[a-zA-Z0-9\\.\\-]+$");
	std::cout << "Enter username: ";
	std::getline(std::cin, username);
	while (!std::regex_match(username, usernameReg) || !isItUnique(users, username))
	{
		std::cout << "The username must have at least one character and no spaces!" << std::endl;
		std::cout << "Enter username: ";
		std::getline(std::cin, username);
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
	std::cout << "The new user is added successfully!" << std::endl;
}

void Admin::removeUser(std::vector<User*>& users, const std::string& username) const
{
	size_t usersLen = users.size();
	if (getUsername() == username)
	{
		std::cout << "You cannot remove yourself!" << std::endl;
		return;
	}
	for (size_t i = 0; i < usersLen; i++)
	{
		if (users[i]->getUsername() == username)
		{
			users.erase(users.begin() + i);
			std::cout << "The user is removed successfully!" << std::endl;
			return;
		}
	}
	std::cout << "There is no user with this username!" << std::endl;
}

void Admin::validateTitleAuthorGenre(std::string& criteria, const std::string& which) const
{
	std::regex reg("^[^ ][a-zA-Z\\.\\- ]+$");
	std::cout << "Enter the " << which << " of the book: ";
	std::getline(std::cin, criteria);
	while (!std::regex_match(criteria, reg))
	{
		std::cout << "The " << which << " must contain only letters and have length more than zero!" << std::endl;
		std::cout << "Your answer: ";
		std::getline(std::cin, criteria);
	}
}

void Admin::validatePubYear(int& num) const
{
	std::regex reg("^[0-9]+$");
	std::string numStr;
	std::cout << "Enter the publication year of the book: ";
	std::getline(std::cin, numStr);
	std::time_t t = std::time(nullptr);
	std::tm* localTime = std::localtime(&t);
	int currentYear = localTime->tm_year + 1900;
	while (true)
	{
		if (!std::regex_match(numStr, reg))
		{
			std::cout << "Invalid year!" << std::endl;
			std::cout << "Your answer: ";
			std::getline(std::cin, numStr);
			continue;
		}
		else 
		{
			num = std::stoi(numStr);
			if (num > currentYear)
			{
				std::cout << "Invalid year!" << std::endl;
				std::cout << "Your answer: ";
				std::getline(std::cin, numStr);
				continue;
			}
		}
		return;
	}
	num = std::stoi(numStr);
}

int Admin::findFirstEmptyIndex(std::vector<Book>& books) const
{
	size_t booksLen = books.size();
	int index = booksLen;
	for (size_t i = 0; i < booksLen; i++)
	{
		if (!books[i].getAvailability() && books[i].getId() < index)
		{
			index = books[i].getId();
		}
	}
	return index;
}

void Admin::addBook(std::vector<Book>& books, int& counter) const
{
	std::string title, author, genre, ratingStr;
	int pubYear, rating;

	validateTitleAuthorGenre(title, "title");
	validateTitleAuthorGenre(author, "author");
	validateTitleAuthorGenre(genre, "genre");
	validatePubYear(pubYear);
	rating = validateRating();

	int firstEmpty = findFirstEmptyIndex(books);

	if (firstEmpty < books.size())
	{
		books[counter] = Book(firstEmpty, title, author, genre, pubYear, rating);
	}
	else
	{
		books.push_back(Book(firstEmpty, title, author, genre, pubYear, rating));
	}

	counter++;
	std::cout << "The book is added successfully!" << std::endl;
}

void Admin::swapBooks(Book& b1, Book& b2) const
{
	Book tempBook = b2;
	b2 = b1;
	b1 = tempBook;
}


void Admin::removeBook(std::vector<Book>& books, int id, int& counter) const
{
	books[id].setAvailability(false);
	swapBooks(books[id], books[counter - 1]);
	counter--;
	std::cout << "The book is removed successfully!" << std::endl;
}

void Admin::validateKeyWord(std::string& word) const
{
	std::regex wordReg("^[^ ][a-zA-Z0-9\\.\\-]+$");
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
	std::regex descReg("^[^ ].+[^ ]$");
	std::cout << "Enter the description: ";
	std::getline(std::cin, desc);
	while (!std::regex_match(desc, descReg))
	{
		std::cout << "The description must be at least 1 character long" << std::endl;
		std::cout << "and should not start or end with space!" << std::endl;
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
