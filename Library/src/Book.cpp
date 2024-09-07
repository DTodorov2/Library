#include "../include/Book.h"

int Book::getId() const
{
	return id;
}

size_t Book::getPublicationYear() const
{
	return publicationYear;
}

size_t Book::getRating() const
{
	return rating;
}

const std::string& Book::getHeading() const
{
	return heading;
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

Book::Book(int id, const std::string& title, const std::string& author, const std::string& genre, size_t publicationYear, size_t rating)
{
	this->id = id;
	heading = title;
	this->author = author;
	this->genre = genre;
	this->publicationYear = publicationYear;
	this->rating = rating;
}

void Book::setId(int id)
{
	this->id = id;
}
