#include "../include/Book.h"
#include "../include/Helper.h"
#include <iostream>

int Book::getId() const
{
	return id;
}

size_t Book::getPublicationYear() const
{
	return publicationYear;
}

double Book::getRating() const
{
	return rating;
}

const std::string& Book::getTitle() const
{
	return title;
}

const std::string& Book::getAuthor() const
{
	return author;
}

const std::string& Book::getGenre() const
{
	return genre;
}

const std::set<std::string>& Book::getKeyWords() const
{
	return keyWords;
}

bool Book::getAvailability() const
{
	return isAvailable;
}


Book::Book(int id, const std::string& title, const std::string& author, const std::string& genre, size_t publicationYear, double rating)
{
	this->id = id;
	this->title = title;
	this->author = author;
	this->genre = genre;
	this->publicationYear = publicationYear;
	this->rating = rating;
	isAvailable = true;
}

void Book::setAvailability(bool isAv)
{
	this->isAvailable = isAv;
}

void Book::addKeyWord(const std::string& word)
{
	keyWords.insert(word);
	std::cout << "Word " << word << " added successfully!" << std::endl;
}

void Book::addRating(int newRating)
{
	rating = (rating + newRating) / 2.0;
}

void Book::addRatedPerson(const std::string& username)
{
	ratedPeople.insert(username);
}

void Book::removeRatedPerson(const std::string& username)
{
	ratedPeople.erase(username);
}

bool Book::hasRated(const std::string& username) const
{
	if (ratedPeople.find(username) != ratedPeople.end())
	{
		return true;
	}
	return false;
}

void Book::setDesc(const std::string& desc)
{
	this->description = desc;
}

void Book::setId(int id)
{
	this->id = id;
}




void Book::writeToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&id, sizeof(id));

	Helper::writeStringToFile(ofs, author);
	Helper::writeStringToFile(ofs, title);
	Helper::writeStringToFile(ofs, genre);
	Helper::writeStringToFile(ofs, description);
	
	ofs.write((const char*)&publicationYear, sizeof(publicationYear));

	Helper::writeSetOfStringToFile(ofs, keyWords);

	ofs.write((const char*)&rating, sizeof(rating));
	ofs.write((const char*)&isAvailable, sizeof(isAvailable));

	Helper::writeSetOfStringToFile(ofs, ratedPeople);
}

void readBookFromFile(Book& book, std::ifstream& ifs)
{
	ifs.read((char*)&book.id, sizeof(book.id));

	Helper::readStringFromFile(ifs, book.author);
	Helper::readStringFromFile(ifs, book.title);
	Helper::readStringFromFile(ifs, book.genre);
	Helper::readStringFromFile(ifs, book.description);

	ifs.read((char*)&book.publicationYear, sizeof(book.publicationYear));

	Helper::readSetOfStringFromFile(ifs, book.keyWords);

	ifs.read((char*)&book.rating, sizeof(book.rating));
	ifs.read((char*)&book.isAvailable, sizeof(book.isAvailable));

	Helper::readSetOfStringFromFile(ifs, book.ratedPeople);
}