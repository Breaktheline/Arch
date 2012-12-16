#ifndef H_OPTIONS
#define H_OPTIONS

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
	TList<char*>* Dirs;
	
};

#endif