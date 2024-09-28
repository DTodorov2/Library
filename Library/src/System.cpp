#include "../include/Library.h"
#include <string>
#include <iostream>
#include <regex>

#include <map>

// Constants for menu options
const std::map<int, std::string> menuOptions = {
	{1, "Login"}, {2, "Logout"}, {3, "Open file"}, {4, "Close file"}, {5, "Save file"},
	{6, "Save file as"}, {7, "Help"}, {8, "Show all books info"}, {9, "Show a book info"},
	{10, "Find a book"}, {11, "Add key words to a book"}, {12, "Add description to a book"},
	{13, "Rate a book"}, {14, "Sort the books"}, {15, "Add user"}, {16, "Remove user"},
	{17, "Add book"}, {18, "Remove book"}, {19, "Exit"}
};

// Function for validating options
void validateOption(std::string& option)
{
	std::regex optionRegex("^([1-9]|1[0-9])$");

	std::getline(std::cin, option);

	while (!std::regex_match(option, optionRegex)) {
		std::cout << "The number must be between 1 and 19: ";
		std::getline(std::cin, option);
	}
}

// Function to display the menu and get a valid key
int chooseKey()
{
	std::cout << "-------------------" << std::endl;
	for (auto it = menuOptions.begin(); it != menuOptions.end(); ++it) {
		std::cout << it->first << " - " << it->second << std::endl;
	}
	std::cout << "-------------------" << std::endl;

	std::cout << "Choose an option: ";
	std::string optionStr;
	validateOption(optionStr);
	return std::stoi(optionStr);
}

// Function to validate file name
void validateFileName(std::string& fileName)
{
	std::regex fileNameReg("^[a-zA-Z0-9]+\\.txt$");
	std::cout << "Enter a file name with .txt extension or type \"exit\": ";

	while (true) {
		std::getline(std::cin, fileName);
		if (fileName == "exit") {
			std::cout << "Thank you for using our platform!" << std::endl;
			exit(0);
		}
		if (std::regex_match(fileName, fileNameReg)) {
			break;
		}
		std::cout << "Invalid file name! The file name must have .txt extension and be at least one character long." << std::endl;
	}
}



void executeOption(Library& lib, int key, std::string& fileName)
{

	switch (key)
	{
	case 1:
		{
			std::string username, pass;
			std::cout << "Enter username: ";
			std::getline(std::cin, username);
			std::cout << "Enter password: ";
			std::getline(std::cin, pass);
			lib.login(username, pass);
			break;
		}
	case 2:
		lib.logout();
		break;
	case 3:
		validateFileName(fileName);
		try
		{
			lib.open(fileName);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << " - File name: " << fileName << std::endl;
		}
		break;
	case 4:
		lib.close(fileName);
		break;
	case 5:
		lib.save(fileName);
		break;
	case 6:
		lib.saveAs(fileName);
		break;
	case 7:
		lib.help();
		break;
	case 8:
		lib.initiateShowingAllBooksInfo();
		break;
	case 9:
		lib.initiateShowingCurrentBookInfo();
		break;
	case 10:
		lib.initiateFindingBook();
		break;
	case 11:
		lib.initiateAddingKeyWords();
		break;
	case 12:
		lib.initiateAddingDesc();
		break;
	case 13:
		lib.initiateRatingBook();
		break;
	case 14:
		lib.initiateSortingBooks();
		break;
	case 15:
		lib.initiateAddingUser();
		break;
	case 16:
		lib.initiateRemovingUser();
		break;
	case 17:
		lib.initiateAddingBook();
		break;
	case 18:
		lib.initiateRemovingBook();
		break;
	case 19:
		std::cout << "Thank you for using our platform!" << std::endl;
		exit(0);
		break;
	default:
		break;
	}
	std::cout << std::endl;
	system("pause");
	system("cls");
}


int runProgram()
{
	Library lib;
	std::string fileName;
	validateFileName(fileName);
	try
	{
		lib.open(fileName);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << " - File name: " << fileName << std::endl;
		exit(1);
	}

	while (true)
	{
		int key = 0;
		key = chooseKey();
		executeOption(lib, key, fileName);
	}
}


int main()
{
	runProgram();
}