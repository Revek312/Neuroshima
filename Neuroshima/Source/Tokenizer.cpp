#include "..\Include\Tokenizer.hpp"

Tokenizer::Tokenizer()
{
}


Tokenizer::~Tokenizer()
{
}

Tokenizer::TokenType Tokenizer::checkType(std::string & str)
{
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] < 48 || str[i] > 57) return Tokenizer::TokenType::String;
	}
	return Tokenizer::TokenType::Int;
}

bool Tokenizer::tokenize(std::string & filePath, std::vector<Token>& tokens, std::string & logPath)
{

	bool logged = false;
	if (logPath != "") logged = true;

	std::ifstream source(filePath);
	std::ofstream log;
	if (logged) log.open(logPath);

	/* Check for errors with files */

	if (!log.good()) {
		logged = false;
		printf_s("ERROR::LOG_FILE::UNABLE_TO_OPEN\n");
	}

	if (!source.good()) {
		printf_s("ERROR::SOURCE_FILE::UNABLE_TO_OPEN\n");
		if (logged) log << "ERROR::SOURCE_FILE::UNABLE_TO_OPEN\n";
		return false;
	}

	std::string str;

	Token tukan;
	TokenType species;

	/* Tokenize a file */

	while (!source.eof()) {

		source >> str;
		species = checkType(str);
		tukan.type = species;
		if (species == TokenType::Int)
			tukan.val = std::stoi(str);
		else
			tukan.val = 0;
		tukan.str = str;

		tokens.push_back(tukan);

		if (logged) {
			log << str << " -> ";
			if (tukan.type == TokenType::Int) log << "int = " << tukan.val << "\n";
			else log << "str = \"" << tukan.str << "\"\n";
			log.flush();
		}
	}

	return true;
}

Tokenizer::Token::Token()
{
	type = TokenType::Error;
	str = "";
}

Tokenizer::Token::~Token()
{
}
