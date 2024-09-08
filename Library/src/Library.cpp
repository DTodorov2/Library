#include "../include/Library.h"
#include <iostream>
#include <fstream>



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
	throw std::exception("No such user exists!");
}

void Library::logout()
{
	currentUserIndex = -1;
	std::cout << "You logged out successfully!" << std::endl;
}

template <typename T>
void Library::readFromFile(const std::ifstream& ifs, std::vector<T>& vec)
{
	size_t vecLen = vec.size();
	for (size_t i = 0; i < vecLen; i++)
	{
		vec[i].readFromFile(ifs);
	}
}

template <typename T>
void Library::writeToFile(const std::ofstream& ofs, const std::vector<T>& vec) const
{
	size_t vecLen = vec.size();
	for (size_t i = 0; i < vecLen; i++)
	{
		vec[i].writeToFile(ofs);
	}
}

void Library::open(const std::string& fileName) //opens a File
{
	std::ifstream ifs(fileName, std::ios::in | std::ios::out);
	if (!ifs.is_open())
	{
		throw std::exception("Could not open a file!");
	}
	readFromFile(ifs, books);
	readFromFile(ifs, users);
	ifs.close();
}

void Library::close(std::string& fileName) // closes a file
{
	fileName = "exit";
	std::cout << "File closed successfully!" << std::endl;
}

void Library::save(const std::string& fileName) const
{
	std::ofstream ofs(fileName, std::ios::in | std::ios::out | std::ios::trunc);
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

void Library::setCurrentUserIndex(int id)
{
	currentUserIndex = id;
}

template void Library::readFromFile<Book>(const std::ifstream& ifs, std::vector<Book>& vec);
template void Library::readFromFile<User*>(const std::ifstream& ifs, std::vector<User*>& vec);

template void Library::writeToFile<Book>(const std::ofstream& ofs, const std::vector<Book>& vec) const;
template void Library::writeToFile<User*>(const std::ofstream& ofs, const std::vector<User*>& vec) const;