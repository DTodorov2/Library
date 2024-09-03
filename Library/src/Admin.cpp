#include "../include/Admin.h"

Admin::Admin(const std::string& username, const std::string& pass) : User(username, pass, true) {};

bool Admin::addUser(std::vector<User*>& users, const std::string& username, const std::string& pass) const
{

}

bool Admin::removeUser(std::vector<User*>& users, const std::string& username) const
{

}

bool Admin::addBook(std::vector<Book>& books) const
{

}

bool Admin::removeBook(std::vector<Book>& books) const
{

}