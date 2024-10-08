#include "../include/Library.h"
#include "../include/Helper.h"
#include <iostream>
#include <fstream>
#include <regex>

void Library::login(const std::string& username, const std::string& pass)
{
	if (currentUserIndex != -1)
	{
		std::cout << "You are already logged in as " << users[currentUserIndex]->getUsername() << "!" << std::endl;
		return;
	}
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
	if (currentUserIndex == -1)
	{
		std::cout << "You are already logged out!" << std::endl;
		return;
	}
	currentUserIndex = -1;
	std::cout << "You logged out successfully!" << std::endl;
}

void Library::readFromFile(std::ifstream& ifs, std::vector<User*>& vec)
{
	vec.clear();
	size_t vecLen = 0;
	ifs.read((char*)&vecLen, sizeof(vecLen));
	for (size_t i = 0; i < vecLen; i++)
	{
		std::string username, pass;
		bool isAdmin;
		Helper::readUserFromFile(ifs, username, pass, isAdmin);
		vec.push_back(Helper::UserFactory(username, pass, isAdmin));
	}
}

void Library::readFromFile(std::ifstream& ifs, std::vector<Book>& vec)
{
	vec.clear();
	size_t vecLen = 0;
	ifs.read((char*)&vecLen, sizeof(vecLen));
	for (size_t i = 0; i < vecLen; i++)
	{
		Book newBook;
		readBookFromFile(newBook, ifs);
		vec.push_back(newBook);
	}
}


void Library::writeToFile(std::ofstream& ofs, const std::vector<User*>& vec) const
{
	size_t vecLen = vec.size();
	ofs.write((const char*)&vecLen, sizeof(vecLen));
	for (size_t i = 0; i < vecLen; i++)
	{
		vec[i]->writeToFile(ofs);
	}
}

void Library::writeToFile(std::ofstream& ofs, const std::vector<Book>& vec) const
{
	size_t vecLen = vec.size();
	ofs.write((const char*)&vecLen, sizeof(vecLen));
	for (size_t i = 0; i < vecLen; i++)
	{
		vec[i].writeToFile(ofs);
	}
}

void Library::open(const std::string& fileName)
{
	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::exception("Could not open a file");
	}
	readFromFile(ifs, books);
	readFromFile(ifs, users);
	ifs.close();

	if (users.size() == 0)
	{
		addUser("admin", "i<3c++", true);
	}

	std::cout << "You opened the file successfully!" << std::endl;
}

void Library::close(std::string& fileName)
{
	if (fileName == "exit")
	{
		std::cout << "You have not opened a file yet!" << std::endl;
		return;
	}
	fileName = "exit";
	std::cout << "File closed successfully!" << std::endl;
}

void Library::save(const std::string& fileName) const
{
	if (fileName == "exit")
	{
		std::cout << "You have not opened a file yet!" << std::endl;
		return;
	}
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
	std::regex regFileName("^[a-zA-Z0-9]+\\.txt$");
	std::cout << "Enter file name: ";
	std::getline(std::cin, fileName);
	while (!std::regex_match(fileName, regFileName))
	{
		std::cout << "The file name must be at least one character!" << std::endl;
		std::cout << "Enter file name: ";
		std::getline(std::cin, fileName);
	}
}

void Library::saveAs(const std::string& fileName) const
{
	if (fileName == "exit")
	{
		std::cout << "You have not opened a file yet!" << std::endl;
		return;
	}
	std::string newFileName;
	validateFileName(newFileName);
	// if a client enter "exit" as a name, the function stops
	if (newFileName == "exit") 
	{
		return;
	}
	save(newFileName);
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
	if (!canProceed())
	{
		return;
	}

	users[currentUserIndex]->booksAll(books);
}

int Library::validateId(const std::string& what) const
{
	std::string idStr;
	std::regex idReg("^[0-9]+$");
	std::cout << "Id of the book you want to " << what << " or \"exit\": ";
	std::getline(std::cin, idStr);
	while (!std::regex_match(idStr, idReg))
	{
		if (idStr == "exit")
		{
			return -1;
		}
		std::cout << "The id must contain digits only!" << std::endl;
		std::cout << "Id of the book you want to " << what << " or \"exit\": ";
		std::getline(std::cin, idStr);
	}

	int id = std::stoi(idStr);

	int booksLen = books.size();
	for (size_t i = 0; i < booksLen; i++)
	{
		if (books[i].getId() == id)
		{
			return i;
		}
	}

	std::cout << "No such book!" << std::endl;
	return -1;
}

void Library::initiateShowingCurrentBookInfo() const
{
	if (!canProceed())
	{
		return;
	}

	std::string idStr;
	int id = validateId("see");
	if (id == -1)
	{
		return;
	}
	users[currentUserIndex]->booksView(books, id);
}

void Library::validateFindingOption(std::string& option) const
{
	std::regex optionReg("^(title|author|key word)$");
	std::cout << "Enter option (must be title, author or key word): ";
	std::getline(std::cin, option);
	if (!std::regex_match(option, optionReg))
	{
		std::cout << "The option must be title, author or key word!" << std::endl;
		std::cout << "Enter option: ";
		std::getline(std::cin, option);
	}
}

void Library::validateSortingOption(std::string& option) const
{
	std::regex optionReg("^(title|author|year|rating)$");
	std::cout << "Enter option (must be title, author, year, rating): ";
	std::getline(std::cin, option);
	while (!std::regex_match(option, optionReg))
	{
		std::cout << "The option must be title, author, year or rating!" << std::endl;
		std::cout << "Enter option: ";
		std::getline(std::cin, option);
	}
}

void Library::initiateFindingBook() const
{
	if (!canProceed())
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
	if (!canProceed())
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

	// removes the person from the set for rating
	size_t booksLen = books.size();
	for (size_t i = 0; i < booksLen; i++)
	{
		books[i].removeRatedPerson(username);
	}
}

void Library::initiateAddingBook()
{
	if (!isLoggedIn())
	{
		return;
	}

	users[currentUserIndex]->addBook(books);
}

void Library::initiateRemovingBook()
{
	if (!canProceed())
	{
		return;
	}
	std::string idStr;
	int id = validateId("remove");
	if (id == -1)
	{
		return;
	}
	users[currentUserIndex]->removeBook(books, id);
}

bool Library::canProceed() const
{
	if (!isLoggedIn())
	{
		return false;
	}
	if (books.size() == 0)
	{
		std::cout << "No books available!" << std::endl;
		return false;
	}
	return true;
}


void Library::initiateAddingKeyWords()
{
	if (!canProceed())
	{
		return;
	}
	std::string idStr;
	int id = validateId("add words to");
	if (id == -1)
	{
		return;
	}
	users[currentUserIndex]->addKeyWords(books, id);
}

void Library::initiateAddingDesc()
{
	if (!canProceed())
	{
		return;
	}
	std::string idStr;
	int id = validateId("add description to");
	if (id == -1)
	{
		return;
	}
	users[currentUserIndex]->addDesc(books, id);
}

void Library::initiateRatingBook()
{
	if (!canProceed())
	{
		return;
	}
	std::string idStr;
	int id = validateId("rate");
	if (id == -1)
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