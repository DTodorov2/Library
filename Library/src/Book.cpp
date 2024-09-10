#include "../include/Book.h"
#include <fstream>

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

bool Book::getAvailability() const
{
	return isAvailable;
}


Book::Book(int id, const std::string& title, const std::string& author, const std::string& genre, size_t publicationYear, size_t rating)
{
	this->id = id;
	heading = title;
	this->author = author;
	this->genre = genre;
	this->publicationYear = publicationYear;
	this->rating = rating;
	isAvailable = true;
}

void Book::setId(int id)
{
	this->id = id;
}

void Book::setAvailability(bool isAv)
{
	this->isAvailable = isAv;
}

void Book::writeToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&id, sizeof(id));

	int authorLen = author.size();
	ofs.write((const char*)&authorLen, sizeof(authorLen));
	ofs.write(author.c_str(), authorLen);

	int headingLen = heading.size();
	ofs.write((const char*)&headingLen, sizeof(headingLen));
	ofs.write(heading.c_str(), headingLen);

	int genreLen = genre.size();
	ofs.write((const char*)&genreLen, sizeof(genreLen));
	ofs.write(genre.c_str(), genreLen);

	int descriptionLen = description.size();
	ofs.write((const char*)&descriptionLen, sizeof(descriptionLen));
	ofs.write(description.c_str(), descriptionLen);
	
	ofs.write((const char*)&publicationYear, sizeof(publicationYear));

	int keyWordsLen = keyWords.size();
	ofs.write((const char*)&keyWordsLen, sizeof(keyWordsLen));
	for (std::set<std::string>::iterator it = keyWords.begin(); it != keyWords.end(); ++it)
	{
		int currWordLen = it->size();
		ofs.write((const char*)&currWordLen, sizeof(currWordLen));
		ofs.write(it->c_str(), currWordLen);
	}

	ofs.write((const char*)&rating, sizeof(rating));
}

void Book::readFromFile(std::ifstream& ifs)
{
	ifs.read((char*)&id, sizeof(id));

	int authorLen = 0;
	ifs.read((char*)&authorLen, sizeof(authorLen));
	author.resize(authorLen);
	ifs.read(&author[0], authorLen);

	int headingLen = 0;
	ifs.read((char*)&headingLen, sizeof(headingLen));
	heading.resize(headingLen);
	ifs.read(&heading[0], headingLen);

	int genreLen = 0;
	ifs.read((char*)&genreLen, sizeof(genreLen));
	genre.resize(genreLen);
	ifs.read(&genre[0], genreLen);

	int descriptionLen = 0;
	ifs.read((char*)&descriptionLen, sizeof(descriptionLen));
	description.resize(descriptionLen);
	ifs.read(&description[0], descriptionLen);

	ifs.read((char*)&publicationYear, sizeof(publicationYear));

	int keyWordsLen = 0;
	ifs.read((char*)&keyWordsLen, sizeof(keyWordsLen));
	for (size_t i = 0; i < keyWordsLen; i++)
	{
		int currWordLen = 0;
		ifs.read((char*)&currWordLen, sizeof(currWordLen));
		std::string currWord(currWordLen, '\0');
		ifs.read(&currWord[0], currWordLen);
		keyWords.insert(currWord);
	}

	ifs.read((char*)&rating, sizeof(rating));
}