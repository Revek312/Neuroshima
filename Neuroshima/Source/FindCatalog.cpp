#include "..\Include\FindCatalog.hpp"




FindCatalog::FindCatalog(std::string catalogPath, bool debugMode)
{
	_debug = debugMode;
	loadCatalog(catalogPath);
	buildReferences();
}

FindCatalog::~FindCatalog()
{
}

void FindCatalog::loadCatalog(std::string path)
{
	Tokenizer tokenizer;

	std::vector <Tokenizer::Token> tokens;
	std::string logPath("");
	if (!tokenizer.tokenize(path, tokens, logPath))
		return;
	
	printf_s("Tokens count: %d\n", tokens.size());

	FindCatalog::Find currentFind;
	FindCatalog::Item currentItem;
	unsigned int ID = 1;

	std::vector <Tokenizer::Token>::iterator left = tokens.begin();
	std::vector <Tokenizer::Token>::iterator right = tokens.begin() + 1;

	while (left < tokens.end()) {

		while (left->str != "#")
			++left;
		++left;
		right = left + 1;
		while (right < tokens.end() &&  right->str[0] != '#')
			++right;
		/* #-------------#  */
		/* -l------------r	*/

		/* Load name */
		currentFind.ID = ID;
		++ID;
		currentFind.name = "";
		currentFind.items.clear();

		while (left < right && left->type == Tokenizer::TokenType::String) {
			currentFind.name += left->str + " ";
			++left;
		}

		/* Load items */

		while (left < right - 1) {
			/* Roll value */
			currentItem.type = ItemType::Normal;
			currentItem.desc = "";
			currentItem.roll = left->val;
			++left;

			/* Description */
			while (left < right && left->type == Tokenizer::TokenType::String) {
				if (left->str == "(*)") {
					currentItem.type = ItemType::Reference;
				}
				else {
					currentItem.desc += left->str + " ";
				}
				++left;
			}
			currentItem.desc.pop_back();
			currentFind.items.push_back(currentItem);
			printf_s("Item: %d %s\n", currentItem.roll, currentItem.desc.c_str());
		}


		left = right;
		catalog.push_back(currentFind);
		printf_s("\n");
	}
}

void FindCatalog::showCatalog()
{
	printf_s("Finds count: %d\n\n", catalog.size());
	for (int i = 0; i < catalog.size(); ++i) {
		printf_s("%d %s [%d]\n", catalog[i].ID, catalog[i].name.c_str(), catalog[i].items.size());
		for (int j = 0; j < catalog[i].items.size(); ++j) {
			printf_s(" | %d %s\n", catalog[i].items[j].roll, catalog[i].items[j].desc.c_str());
		}
	}
}

void FindCatalog::buildReferences()
{
}
