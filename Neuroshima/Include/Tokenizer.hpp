#ifndef N_TOKENIZER_HPP
#define N_TOKENIZER_HPP

#include <string>
#include <fstream>
#include <vector>
#include <string>

class Tokenizer
{
public:
	static enum TokenType {
		Int,
		String,
		Error
	};
	static struct Token {
		TokenType type;

		std::string str;
		int val;

		Token();
		~Token();

	};

	Tokenizer();
	~Tokenizer();

	TokenType checkType(std::string& str);
	bool tokenize(std::string& filePath, std::vector<Token>& tokens, std::string& logPath);
};


#endif