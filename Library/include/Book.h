#pragma once
#include <string>
#include <vector>
#include <set>

class Book
{
	int id;
	std::string author;
	std::string heading;
	std::string genre; //moje da e enum
	std::string description;
	size_t publicationYear;
	std::set<std::string> keyWords; // using set and not unordered set, cause the worst case scenario is O(n) and for set is log(n)
	size_t rating;

public:
	Book(int id, const std::string& title, const std::string& author, const std::string& genre, size_t publicationYear, size_t rating);

	int getId() const;
	size_t getPublicationYear() const;
	size_t getRating() const;
	const std::string& getHeading() const;
	const std::string& getAuthor() const;
	const std::string& getGenre() const;
	const std::set<std::string>& getKeyWords() const;

	void setId(int id);

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
	//add key word
	//set description
};