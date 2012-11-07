#ifndef H_LZW_DECODER
#define H_LZW_DECODER

#include "stdio.h"
#include "Common.h"
#include "HashTree.h"

class LzwDecoder
{
public:
	void Decode(FILE* inputFile, FILE* outputFile);

private:
	HashTree _hashTree;
};

#endif