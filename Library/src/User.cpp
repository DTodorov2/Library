#include "../include/User.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <regex>

User::User(const std::string& username, const std::string& pass, bool isAdmin)
{
	this->username = username;
	this->password = pass;
	this->isAdmin = isAdmin;
}

const std::string& User::getUsername() const
{
	return username;
}

const std::string& User::getPass() const
{
	return password;
}

bool User::isAdministrator() const
{
	return isAdmin;
}

void User::printBook(const Book& book) const
{
	if (!book.getAvailability())
	{
		return;
	}
	std::cout << "\nBook number: ";
	std::cout << book.getId() << std::endl;
	std::cout << "Title: " << book.getHeading() << std::endl;
	std::cout << "Author: " << book.getAuthor() << std::endl;
	std::cout << "Genre: " << book.getGenre() << std::endl;
	std::cout << "Publication Year: " << book.getPublicationYear() << std::endl;
	std::cout << "Rating: " << book.getRating() << std::endl;
}

int User::validateRating() const
{
	std::string rating;
	std::regex ratingReg("^[0-5]$");
	std::cout << "Enter the rating: ";
	std::getline(std::cin, rating);
	while (!std::regex_match(rating, ratingReg))
	{
		std::cout << "The rating must be between 0 and 5!" << std::endl;
		std::cout << "Enter the rating: ";
		std::getline(std::cin, rating);
	}

	return std::stoi(rating);
}

void User::booksAll(const std::vector<Book>& books) const
{
	size_t countBooks = books.size();
	for (size_t i = 0; i < countBooks; i++)
	{
		printBook(books[i]);
	}
}

void User::booksFind(const std::vector<Book>& books, const std::string& option, const std::string& optionString) const
{
	size_t booksLen = books.size();
	for (size_t i = 0; i < booksLen; i++)
	{
		if (option == "title" && books[i].getHeading() == optionString)
		{
			printBook(books[i]);
		}
		else if (option == "author" && books[i].getAuthor() == optionString)
		{
			printBook(books[i]);
		}
		else if (option == "tag" && books[i].getKeyWords().find(optionString) != books[i].getKeyWords().end())
		{
			printBook(books[i]);
		}
	}
}

void User::booksView(const std::vector<Book>& books, int bookId) const
{
	printBook(books[bookId]);
}

void User::sortBooksTitle(std::vector<Book>& books, bool ascending)
{
	auto compare = [ascending](const Book& a, const Book& b)
	{
		if (ascending) {
			return a.getHeading() < b.getHeading();
		}
		return a.getHeading() > b.getHeading();
	};

	std::sort(books.begin(), books.end(), compare);
}

void User::sortBooksAuthor(std::vector<Book>& books, bool ascending)
{
	auto compare = [ascending](const Book& a, const Book& b)
	{
		if (ascending)
		{
			return a.getAuthor() < b.getAuthor();
		}
		return a.getAuthor() > b.getAuthor();
	};

	std::sort(books.begin(), books.end(), compare);
}

void User::sortBooksYear(std::vector<Book>& books, bool ascending)
{
	auto compare = [ascending](const Book& a, const Book& b)
	{
		if (ascending)
		{
			return a.getPublicationYear() < b.getPublicationYear();
		}
		return a.getPublicationYear() > b.getPublicationYear();
	};

	std::sort(books.begin(), books.end(), compare);
}

void User::sortBooksRating(std::vector<Book>& books, bool ascending)
{
	auto compare = [ascending](const Book& a, const Book& b)
	{
		if (ascending)
		{
			return a.getRating() < b.getRating();
		}
		return a.getRating() > b.getRating();
	};

	std::sort(books.begin(), books.end(), compare);
}

void User::booksSort(std::vector<Book>& books, const std::string& option, bool isAsc)
{
	if (option == "title")
	{
		sortBooksTitle(books, isAsc);
	}
	else if (option == "author")
	{
		sortBooksAuthor(books, isAsc);
	}
	else if (option == "year")
	{
		sortBooksYear(books, isAsc);
	}
	else
	{
		sortBooksRating(books, isAsc);
	}
	
	size_t booksLen = books.size();
	for (size_t i = 0; i < booksLen; i++)
	{
		if (books[i].getId() != -1)
		{
			books[i].setId(i);
		}
	}
	std::cout << "The books are sorted successfully!" << std::endl;
}

void User::writeToFile(std::ofstream& ofs) const
{
	int usernameLen = username.size();
	ofs.write((const char*)&usernameLen, sizeof(usernameLen));
	ofs.write((const char*)username.c_str(), usernameLen);
	int passLen = password.size();
	ofs.write((const char*)&passLen, sizeof(passLen));
	ofs.write((const char*)password.c_str(), passLen);
	ofs.write((const char*)&isAdmin, sizeof(isAdmin));
}
