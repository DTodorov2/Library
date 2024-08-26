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
};