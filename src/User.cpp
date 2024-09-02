#include "../include/User.h"
#include <iostream>

void User::booksAll(const std::vector<Book>& books) const
{
	size_t countBooks = books.size();
	for (size_t i = 0; i < countBooks; i++)
	{
		std::cout << "Book number: ";
		std::cout << books[i].getId() << std::endl;
		std::cout << books[i].getHeading() << std::endl;
		std::cout << books[i].getAuthor() << std::endl;
		std::cout << books[i].getGenre() << std::endl;
	}
}