#ifndef H_LZW
#define H_LZW

#include "stdio.h"

class Lzw
{
public:
	void Encode(FILE* inputFile, FILE* outputFile);
	void Decode(FILE* inputFile, FILE* outputFile);
};

#endif