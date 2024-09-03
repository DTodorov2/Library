#include "../include/Client.h"
#include <iostream>

Client::Client(const std::string& username, const std::string& pass) : User(username, pass, false) {};

bool Client::addUser(std::vector<User*>& users, const std::string& username, const std::string& pass) const
{
	std::cout << "Sorry, you are not allowed to add users into the system!" << std::endl;
}

bool Client::removeUser(std::vector<User*>& users, const std::string& username) const
{
	std::cout << "Sorry, you are not allowed to remove users from the system!" << std::endl;
}

bool Client::addBook(std::vector<Book>& books, int id) const
{
	std::cout << "Sorry, you are not allowed to add books into the system!" << std::endl;
}

bool Client::removeBook(std::vector<Book>& books, int id) const
{
	std::cout << "Sorry, you are not allowed to remove books from the system!" << std::endl;
}