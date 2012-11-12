#ifndef H_PARSER
#define H_PARSER

#include "Common.h"
#include "Options.h"

class Parser
{
public:
	static const char HYPHEN = '-';
	Options* Parse(int argc, char** argv);

private:
	void SetOption(char arg, Options &options);
};

#endif
