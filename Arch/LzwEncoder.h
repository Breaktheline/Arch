#ifndef H_LZW_ENCODER
#define H_LZW_ENCODER

#include "stdio.h"
#include "Common.h"
#include "HashTree.h"

class LzwEncoder
{
public:
	LzwEncoder();
	void Encode(const char* inputFileName, const char* outputFileName);

	void ChangeCodeLength( int nodeIndex );

	void AddNewNode(byte symbol, unsigned char hashCode, FILE* outputFile);

private:
	byte ReadNextByte(FILE* inputFile);
	void WriteCode(FILE* outputFile, int code);

	HashTree _hashTree;
	int _bitsInCode;
	int _codeSize;
	unsigned int _parent;
};

#endif