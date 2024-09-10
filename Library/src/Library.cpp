#include "../include/Library.h"
#include "../include/Helper.h"
#include <iostream>
#include <fstream>
#include <regex>

void Library::login(const std::string& username, const std::string& pass)
{
	size_t usersLen = users.size();
	for (size_t i = 0; i < usersLen; i++)
	{
		if (users[i]->getUsername() == username && users[i]->getPass() == pass)
		{
			currentUserIndex = i;
			std::cout << "You logged in successfully!" << std::endl;
			return;
		}
	}
	std::cout << "No such user exists!" << std::endl;
}

void Library::logout()
{
	currentUserIndex = -1;
	std::cout << "You logged out successfully!" << std::endl;
}

template <typename T>
void Library::readFromFile(std::ifstream& ifs, std::vector<T>& vec)
{
	vec.clear();
	size_t vecLen = 0;
	ifs.read((char*)&vecLen, sizeof(vecLen));
	for (size_t i = 0; i < vecLen; i++)
	{
		if constexpr (std::is_pointer<T>::value)
		{
			vec[i]->readFromFile(ifs);
		}
		else
		{
			vec[i].readFromFile(ifs);
		}
	}
}

template <typename T>
void Library::writeToFile(std::ofstream& ofs, const std::vector<T>& vec) const
{
	size_t vecLen = vec.size();
	ofs.write((const char*)&vecLen, sizeof(vecLen));
	for (size_t i = 0; i < vecLen; i++)
	{
		if constexpr (std::is_pointer<T>::value)
		{
			vec[i]->writeToFile(ofs);
		}
		else
		{
			vec[i].writeToFile(ofs);
		}
	}
}

void Library::open(const std::string& fileName) //opens a File
{
	std::ifstream ifs(fileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::exception("Could not open a file");
	}
	readFromFile(ifs, books);
	readFromFile(ifs, users);
	ifs.close();
	std::cout << "You opened the file successfully!" << std::endl;
}

void Library::close(std::string& fileName) // closes a file
{
	fileName = "exit";
	std::cout << "File closed successfully!" << std::endl;
}

void Library::save(const std::string& fileName) const
{
	std::ofstream ofs(fileName, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::exception("Could not open a file!");
	}
	writeToFile(ofs, books);
	writeToFile(ofs, users);
	std::cout << "File " << fileName << " saved successfully!" << std::endl;
}

void Library::validateFileName(std::string& fileName) const
{
	std::cout << "Enter file name: ";
	std::getline(std::cin, fileName);
	while (fileName.size() == 0)
	{
		std::cout << "The file name must be at least one character!" << std::endl;
		std::cout << "Enter file name: ";
		std::getline(std::cin, fileName);
	}
}

void Library::saveAs() const
{
	std::string fileName;
	validateFileName(fileName);
	save(fileName);
}

void Library::help() const
{
	std::cout << "The following commands are supported:" << std::endl;
	std::cout << "1. open - opens the wanted file" << std::endl;
	std::cout << "2. close - closes currently opened file" << std::endl;
	std::cout << "3. save - saves the currently open file" << std::endl;
	std::cout << "4. saveAs - saves the currently open file in a new file" << std::endl;
	std::cout << "5. help - prints this information" << std::endl;
	std::cout << "6. exit - exists the program" << std::endl;
}

void Library::initiateShowingAllBooksInfo() const
{
	if (!isLoggedIn())
	{
		return;
	}

	users[currentUserIndex]->booksAll(books);
}

int Library::validateId(std::string& idStr, const std::string& what) const
{
	std::cout << "Id of the book you want to " << what << " or \"exit\": ";
	std::getline(std::cin, idStr);
	int id = std::stoi(idStr);
	size_t booksLen = books.size();
	while (id < 0 || id >= booksLen || books[id].getId() == -1)
	{
		if (idStr == "exit")
		{
			return -1;
		}
		std::cout << "No such book!" << std::endl;
		std::cout << "Id of the book you want to " << what << ": ";
		std::getline(std::cin, idStr);
		id = std::stoi(idStr);
	}
	return id;
}

void Library::initiateShowingCurrentBookInfo() const
{
	if (!isLoggedIn())
	{
		return;
	}

	std::string idStr;
	int id = validateId(idStr, "see");
	if (idStr == "exit")
	{
		return;
	}
	users[currentUserIndex]->booksView(books, id);
}

void Library::validateFindingOption(std::string& option) const
{
	std::regex optionReg("^(title|author|tag)$");
	std::cout << "Enter option (must be title, author or tag): ";
	std::getline(std::cin, option);
	if (!std::regex_match(option, optionReg))
	{
		std::cout << "The option must be title, author or tag!" << std::endl;
		std::cout << "Enter option: ";
		std::getline(std::cin, option);
	}
}

void Library::validateSortingOption(std::string& option) const
{
	std::regex optionReg("^(title|author|year|rating)$");
	std::cout << "Enter option (must be title, author, year, rating): ";
	std::getline(std::cin, option);
	if (!std::regex_match(option, optionReg))
	{
		std::cout << "The option must be title, author, year or rating!" << std::endl;
		std::cout << "Enter option: ";
		std::getline(std::cin, option);
	}
}


void Library::initiateFindingBook() const
{
	if (!isLoggedIn())
	{
		return;
	}

	std::string option, optionStr;
	validateFindingOption(option);
	std::cout << "Enter value of option: ";
	std::getline(std::cin, optionStr);
	users[currentUserIndex]->booksFind(books, option, optionStr);
}

void Library::validateIsAsc(bool& isAsc) const
{
	std::string isAscStr;
	std::regex isAscReg("^(y|yes|n|no)$");
	std::cout << "Do you want it ascending? - (yes or no): ";
	std::getline(std::cin, isAscStr);
	while (!std::regex_match(isAscStr, isAscReg))
	{
		std::cout << "Your answer must be yes or no!" << std::endl;
		std::cout << "Your answer: ";
		std::getline(std::cin, isAscStr);
	}
	if (isAscStr == "yes" || isAscStr == "y")
	{
		isAsc = true;
		return;
	}
	isAsc = false;
}

void Library::initiateSortingBooks()
{
	if (!isLoggedIn())
	{
		return;
	}

	std::string option;
	bool isAsc;

	validateSortingOption(option);
	validateIsAsc(isAsc);

	users[currentUserIndex]->booksSort(books, option, isAsc);
}

void Library::initiateAddingUser()
{
	if (!isLoggedIn())
	{
		return;
	}

	users[currentUserIndex]->addUser(users);
}

int Library::findFirstEmptyIndex() const
{
	int empty = -1;
	int booksLen = books.size();
	for (size_t i = 0; i < booksLen; i++)
	{
		if (!books[i].getAvailability())
		{
			return i;
		}
	}
	return booksLen;
}

bool Library::isLoggedIn() const
{
	if (currentUserIndex == -1)
	{
		std::cout << "You need to login first!" << std::endl;
		return false;
	}
	return true;
}


void Library::initiateRemovingUser()
{
	if (!isLoggedIn())
	{
		return;
	}

	std::string username;
	std::cout << "Enter username: ";
	std::getline(std::cin, username);
	users[currentUserIndex]->removeUser(users, username);
}

void Library::initiateAddingBook()
{
	if (!isLoggedIn())
	{
		return;
	}

	int firstEmptyIndex = findFirstEmptyIndex();
	users[currentUserIndex]->addBook(books, firstEmptyIndex);
}

void Library::initiateRemovingBook()
{
	if (!isLoggedIn())
	{
		return;
	}

	std::string idStr;
	int id = validateId(idStr, "remove");
	if (idStr == "exit")
	{
		return;
	}
	users[currentUserIndex]->removeBook(books, id);
}

void Library::initiateAddingKeyWords()
{
	if (!isLoggedIn())
	{
		return;
	}

	std::string idStr;
	int id = validateId(idStr, "add words to");
	if (idStr == "exit")
	{
		return;
	}
	users[currentUserIndex]->addKeyWords(books, id);
}

void Library::initiateAddingDesc()
{
	if (!isLoggedIn())
	{
		return;
	}

	std::string idStr;
	int id = validateId(idStr, "add words to");
	if (idStr == "exit")
	{
		return;
	}
	users[currentUserIndex]->addDesc(books, id);
}

void Library::initiateRatingBook()
{
	if (!isLoggedIn())
	{
		return;
	}

	std::string idStr;
	int id = validateId(idStr, "rate");
	if (idStr == "exit")
	{
		return;
	}
	users[currentUserIndex]->rateBook(books, id);
}

void Library::setCurrentUserIndex(int id)
{
	currentUserIndex = id;
}

void Library::moveFrom(Library&& other)
{
	users = std::move(other.users);
	books = std::move(other.books);
	other.users.clear();
	other.books.clear();
}
void Library::copyFrom(const Library& other)
{
	size_t usersLen = other.users.size();
	users.clear();
	for (size_t i = 0; i < usersLen; i++)
	{
		users.push_back(other.users[i]);
	}
	books = other.books;
}
void Library::free()
{
	size_t usersLen = users.size();
	for (size_t i = 0; i < usersLen; i++)
	{
		delete users[i];
	}
}
Library::Library(const Library& other)
{
	copyFrom(other);
}

Library::Library(Library&& other)
{
	moveFrom(std::move(other));
}

Library& Library::operator=(const Library& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Library& Library::operator=(Library&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Library::~Library()
{
	free();
}

size_t Library::getUsersLen() const
{
	return users.size();
}

void Library::addUser(const std::string& username, const std::string& pass, bool isAdmin)
{
	users.push_back(Helper::UserFactory(username, pass, isAdmin));
}

template void Library::readFromFile<Book>(std::ifstream& ifs, std::vector<Book>& vec);
template void Library::readFromFile<User*>(std::ifstream& ifs, std::vector<User*>& vec);

template void Library::writeToFile<Book>(std::ofstream& ofs, const std::vector<Book>& vec) const;
template void Library::writeToFile<User*>(std::ofstream& ofs, const std::vector<User*>& vec) const;