#ifndef H_LZW_ENCODER
#define H_LZW_ENCODER

#include "stdio.h"
#include "Common.h"
#include "HashTree.h"

class LzwEncoder
{
public:
	void Encode(const char* inputFileName, const char* outputFileName);
	byte ReadNextByte( FILE* inputFile );
private:
	HashTree hashTree;
};

#endif