#include "../include/User.h"
#include <iostream>
#include <algorithm>

void User::printBook(const Book& book) const
{
	std::cout << "Book number: ";
	std::cout << book.getId() << std::endl;
	std::cout << book.getHeading() << std::endl;
	std::cout << book.getAuthor() << std::endl;
	std::cout << book.getGenre() << std::endl;
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

void User::sortBooksTitle(const std::vector<Book>& books, bool ascending)
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

void User::sortBooksAuthor(const std::vector<Book>& books, bool ascending)
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

void User::sortBooksYear(const std::vector<Book>& books, bool ascending)
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

void User::sortBooksRating(const std::vector<Book>& books, bool ascending)
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

void User::booksSort(const std::vector<Book>& books, const std::string& option, bool isAsc)
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

	std::cout << "The books are sorted successfully!" << std::endl;
}