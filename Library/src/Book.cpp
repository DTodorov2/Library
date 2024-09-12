#include "../include/Book.h"
#include <fstream>
#include <iostream>

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


Book::Book(int id, const std::string& title, const std::string& author, const std::string& genre, size_t publicationYear, double rating)
{
	this->id = id;
	heading = title;
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
	rating = (rating + newRating) / 2;
}

void Book::addRatedPerson(const std::string& username)
{
	ratedPeople.insert(username);
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
	ofs.write((const char*)&isAvailable, sizeof(isAvailable));

	int ratedPeopleLen = ratedPeople.size();
	ofs.write((const char*)&ratedPeopleLen, sizeof(ratedPeopleLen));
	for (std::set<std::string>::iterator it = ratedPeople.begin(); it != ratedPeople.end(); ++it)
	{
		int currNameLen = it->size();
		ofs.write((const char*)&currNameLen, sizeof(currNameLen));
		ofs.write(it->c_str(), currNameLen);
	}
}

void Book::readFromFile(std::ifstream& ifs, int& counter)
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
	ifs.read((char*)&isAvailable, sizeof(isAvailable));
	if (isAvailable)
	{
		counter++;
	}

	int ratedPeopleLen = 0;
	ifs.read((char*)&ratedPeopleLen, sizeof(ratedPeopleLen));
	for (size_t i = 0; i < ratedPeopleLen; i++)
	{
		int currNameLen = 0;
		ifs.read((char*)&currNameLen, sizeof(currNameLen));
		std::string currName(currNameLen, '\0');
		ifs.read(&currName[0], currNameLen);
		ratedPeople.insert(currName);
	}
}