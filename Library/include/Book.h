#pragma once
#include <string>
#include <vector>
#include <set>

class Book
{
	int id;
	std::string author;
	std::string title;
	std::string genre;
	std::string description;
	size_t publicationYear;
	std::set<std::string> keyWords;
	double rating;
	bool isAvailable = true;
	std::set<std::string> ratedPeople;

public:
	Book() = default;
	Book(int id, const std::string& title, const std::string& author, const std::string& genre, size_t publicationYear, double rating);

	int getId() const;
	size_t getPublicationYear() const;
	double getRating() const;
	const std::string& getTitle() const;
	const std::string& getAuthor() const;
	const std::string& getGenre() const;
	const std::set<std::string>& getKeyWords() const;
	bool getAvailability() const;

	void setAvailability(bool isAv);
	void setDesc(const std::string& desc);
	void setId(int id);

	void addRating(int newRating);
	void addRatedPerson(const std::string& username);
	void removeRatedPerson(const std::string& username);

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs, int& counter);
	void addKeyWord(const std::string& word);
	bool hasRated(const std::string& username) const;
};