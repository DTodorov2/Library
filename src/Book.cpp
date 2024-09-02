#include "../include/Book.h"

int Book::getId() const
{
	return id;
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

size_t Book::getPublicationYear() const
{
	return publicationYear;
}

size_t Book::getRating() const
{
	return rating;
}


const std::set<std::string>& Book::getKeyWords() const
{
	return keyWords;
}
