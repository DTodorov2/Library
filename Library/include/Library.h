#pragma once
#include "User.h"
#include "Book.h"

class Library
{
	std::vector<User*> users;
	std::vector<Book> books;

	int currentUserIndex = -1;

	void validateFileName(std::string& fileName) const;

	//template for reading books and users
	template <typename T>
	void readFromFile(const std::ifstream& ifs, std::vector<T>& vec);

	//template for reading books and users
	template <typename T>
	void writeToFile(const std::ofstream& ofs, const std::vector<T>& vec) const;

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
	void open(const std::string& fileName); //opens a File
	void close(std::string& fileName); // closes a file // oshte nz kak
	void save(const std::string& fileName) const;
	void saveAs() const;
	void help() const;

	void setCurrentUserIndex(int id);
};