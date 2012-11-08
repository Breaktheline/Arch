#ifndef H_LZW_ENCODER
#define H_LZW_ENCODER

#include "stdio.h"
#include "Common.h"
#include "HashTree.h"
#include "BitsWriter.h"

class LzwEncoder
{
public:
	LzwEncoder(FILE* inputFile, FILE* outputFile);
	void Encode();

private:
	byte ReadNextByte();
	void WriteCode(int code);
	void AddNewNode(byte symbol, unsigned char hashCode);

	FILE* _inputFile;
	BitsWriter* _bitsWriter;
	HashTree _hashTree;
	unsigned int _parent;
};

#endif