#pragma once
#include "User.h"
#include "Book.h"

class Library
{
	std::vector<User*> users;
	std::vector<Book> books;

	int currentUserIndex = -1;
	//int availableBooks = 0;

	void validateFileName(std::string& fileName) const;
	int validateId(const std::string& what) const;
	void validateFindingOption(std::string& option) const;
	void validateSortingOption(std::string& option) const;
	void validateIsAsc(bool& isAsc) const;

	bool isLoggedIn() const;
	bool canProcceed() const;

	void readFromFile(std::ifstream& ifs, std::vector<User*>& vec);
	void readFromFile(std::ifstream& ifs, std::vector<Book>& vec);

	//template for reading books and users
	void writeToFile(std::ofstream& ofs, const std::vector<Book>& vec) const;
	void writeToFile(std::ofstream& ofs, const std::vector<User*>& vec) const;

	void moveFrom(Library&& other);
	void copyFrom(const Library& other);
	void free();
public:
	//BIG 6
	Library() = default;
	Library(const Library& other);
	Library(Library&& other);
	Library& operator=(const Library& other);
	Library& operator=(Library&& other);
	~Library();

	void login(const std::string& username, const std::string& pass);
	void logout();
	void open(const std::string& fileName);
	void close(std::string& fileName);
	void save(const std::string& fileName) const;
	void saveAs(const std::string& fileName) const;
	void help() const;

	void initiateShowingAllBooksInfo() const;
	void initiateShowingCurrentBookInfo() const;
	void initiateFindingBook() const;
	void initiateSortingBooks();
	void initiateAddingUser();
	void initiateRemovingUser();
	void initiateAddingBook();
	void initiateRemovingBook();
	void initiateAddingKeyWords();
	void initiateRatingBook();
	void initiateAddingDesc();

	void setCurrentUserIndex(int id);

	size_t getUsersLen() const;

	void addUser(const std::string& username, const std::string& pass, bool isAdmin);
};