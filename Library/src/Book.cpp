#include "../include/Book.h"
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

	int authorLen = author.size();
	ofs.write((const char*)&authorLen, sizeof(authorLen));
	ofs.write(author.c_str(), authorLen);

	int headingLen = title.size();
	ofs.write((const char*)&headingLen, sizeof(headingLen));
	ofs.write(title.c_str(), headingLen);

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

void readBookFromFile(Book& book, std::ifstream& ifs)
{
	ifs.read((char*)&book.id, sizeof(book.id));

	int authorLen = 0;
	ifs.read((char*)&authorLen, sizeof(authorLen));
	book.author.resize(authorLen);
	ifs.read(&book.author[0], authorLen);

	int headingLen = 0;
	ifs.read((char*)&headingLen, sizeof(headingLen));
	book.title.resize(headingLen);
	ifs.read(&book.title[0], headingLen);

	int genreLen = 0;
	ifs.read((char*)&genreLen, sizeof(genreLen));
	book.genre.resize(genreLen);
	ifs.read(&book.genre[0], genreLen);

	int descriptionLen = 0;
	ifs.read((char*)&descriptionLen, sizeof(descriptionLen));
	book.description.resize(descriptionLen);
	ifs.read(&book.description[0], descriptionLen);

	ifs.read((char*)&book.publicationYear, sizeof(book.publicationYear));

	int keyWordsLen = 0;
	ifs.read((char*)&keyWordsLen, sizeof(keyWordsLen));
	for (size_t i = 0; i < keyWordsLen; i++)
	{
		int currWordLen = 0;
		ifs.read((char*)&currWordLen, sizeof(currWordLen));
		std::string currWord(currWordLen, '\0');
		ifs.read(&currWord[0], currWordLen);
		book.keyWords.insert(currWord);
	}

	ifs.read((char*)&book.rating, sizeof(book.rating));
	ifs.read((char*)&book.isAvailable, sizeof(book.isAvailable));

	int ratedPeopleLen = 0;
	ifs.read((char*)&ratedPeopleLen, sizeof(ratedPeopleLen));
	for (size_t i = 0; i < ratedPeopleLen; i++)
	{
		int currNameLen = 0;
		ifs.read((char*)&currNameLen, sizeof(currNameLen));
		std::string currName(currNameLen, '\0');
		ifs.read(&currName[0], currNameLen);
		book.ratedPeople.insert(currName);
	}
}