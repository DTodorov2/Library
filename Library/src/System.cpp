#include "../include/Library.h"
#include <string>
#include <iostream>
#include <regex>

void validateOption(std::string& option)
{
	std::getline(std::cin, option);

	while (true)
	{
		if (option.length() == 1 && (option[0] - '0' >= 1 && option[0] - '0' <= 9))
		{
			return;
		}
		if (option.length() == 2 && (option[0] - '0' >= 1 && option[0] - '0' <= 9))
		{
			if (option[1] - '0' >= 0 && option[1] - '0' <= 7)
			{
				return;
			}
		}
		std::cout << "The number must be between 1 and 17: ";
		std::getline(std::cin, option);
	}
}

int chooseKey()
{
	std::cout << "-------------------" << std::endl;
	std::cout << "1 - Login" << std::endl;
	std::cout << "2 - Logout" << std::endl;
	std::cout << "3 - Open file" << std::endl;
	std::cout << "4 - Close file" << std::endl;
	std::cout << "5 - Save file" << std::endl;
	std::cout << "6 - Save file as" << std::endl;
	std::cout << "7 - Help" << std::endl;
	std::cout << "8 - Show all books info" << std::endl;
	std::cout << "9 - Show a book info" << std::endl;
	std::cout << "10 - Find a book" << std::endl;
	std::cout << "11 - Add key words to a book" << std::endl;
	std::cout << "12 - Sort the books" << std::endl;
	std::cout << "13 - Add user" << std::endl;
	std::cout << "14 - Remove user" << std::endl;
	std::cout << "15 - Add book" << std::endl;
	std::cout << "16 - Remove book" << std::endl;
	std::cout << "17 - Exit" << std::endl;
	std::cout << "-------------------" << std::endl;

	std::cout << "Choose an option: ";
	std::string optionStr;
	validateOption(optionStr);
	int optionInt = std::stoi(optionStr);
	return optionInt;
}

void validateFileName(std::string& fileName)
{
	std::regex fileNameReg("^[a-zA-Z0-9]+\.txt$");
	std::cout << "You must open a file before procceeding with the actions or type \"exit\": ";
	std::getline(std::cin, fileName);
	while (!std::regex_match(fileName, fileNameReg))
	{
		if (fileName == "exit")
		{
			std::cout << "Thank you for using our platform!" << std::endl;
			exit(0);
		}
		std::cout << "The file name must have .txt extension and be at least one character long!" << std::endl;
		std::cout << "File name: ";
		std::getline(std::cin, fileName);
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
		lib.open(fileName);
		break;
	case 4:
		lib.close(fileName);
		break;
	case 5:
		lib.save(fileName);
		break;
	case 6:
		lib.saveAs();
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
		lib.initiateSortingBooks();
		break;
	case 13:
		lib.initiateAddingUser();
		break;
	case 14:
		lib.initiateRemovingUser();
		break;
	case 15:
		lib.initiateAddingBook();
		break;
	case 16:
		lib.initiateRemovingBook();
		break;
	case 17:
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
		std::cout << e.what() << "- File name: " << fileName << std::endl;
		exit(1);
	}

	if (lib.getUsersLen() == 0)
	{
		lib.addUser("admin", "i<3c++", true);
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