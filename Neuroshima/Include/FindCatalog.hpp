#ifndef N_FINDCATALOG_HPP
#define N_FINDCATALOG_HPP

#include "Tokenizer.hpp"
#include <cstdio>

class FindCatalog
{
public:
	static enum ItemType {
		Normal,
		Reference,
		Error
	};
	static struct Item {
		int roll;
		std::string desc;
		ItemType type;
		int spec;
		Item() { roll = 21; desc = ""; type = Error; spec = 0; };
	};
	static struct Find {
		std::string name;
		unsigned int ID;
		std::vector <Item> items;

		Find() { name = "", ID = 0, items.resize(21); }
	};

	FindCatalog(std::string catalogPath = "Data/FindsCatalog.txt", bool debugMode = true);
	~FindCatalog();

	void showCatalog();

private: 

	std::vector<FindCatalog::Find> catalog;
	bool _debug;

	void loadCatalog(std::string path);
	void buildReferences();

};


#endif