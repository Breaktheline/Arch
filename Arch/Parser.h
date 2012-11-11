#ifndef H_PARSER
#define H_PARSER

#include "Common.h"

struct Options
{
	Options()
	{
		Test = false;
		List = false;
		Code = false;
		Decode = false;
		Recursive = false;
		Fast = false;
		Best = false;
		Stdin = false;
		Files = new TList<char*>();
	}

	~Options()
	{
		delete Files;
	}

	bool Test;
	bool List;
	bool Code;
	bool Decode;
	bool Recursive;
	bool Fast;
	bool Best;
	bool Stdin;

	TList<char*>* Files;
};

class Parser
{
public:
	static const char HYPHEN = '-';
	Options* Parse(int argc, char** argv);

private:
	void SetOption(char arg, Options &options);
};

#endif
