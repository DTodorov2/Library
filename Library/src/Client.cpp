#include "../include/Client.h"
#include <iostream>

Client::Client(const std::string& username, const std::string& pass) : User(username, pass, false) {};

void Client::addUser(std::vector<User*>& users) const
{
	std::cout << "Sorry, you are not allowed to add users into the system!" << std::endl;
}

void Client::removeUser(std::vector<User*>& users, const std::string& username) const
{
	std::cout << "Sorry, you are not allowed to remove users from the system!" << std::endl;
}

void Client::addBook(std::vector<Book>& books, int id) const
{
	std::cout << "Sorry, you are not allowed to add books into the system!" << std::endl;
}

void Client::removeBook(std::vector<Book>& books, int id) const
{
	std::cout << "Sorry, you are not allowed to remove books from the system!" << std::endl;
}

void Client::addKeyWords(std::vector<Book>& books, int id) const
{
	std::cout << "Sorry, you are not allowed to add key words to books!" << std::endl;
}
