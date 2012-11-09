#ifndef H_LZW_DECODER
#define H_LZW_DECODER

#include "stdio.h"
#include "Common.h"
#include "HashTree.h"
#include "BitsReader.h"

class LzwDecoder
{
public:
	LzwDecoder(FILE* inputFile, FILE* outputFile);
	~LzwDecoder();
	void Decode();
	
private:
	byte GetNextSymbol(int code);

	FILE* _outputFile;
	BitsReader* _bitsReader;
	HashTree _hashTree;
	unsigned int _parent;
};

#endif