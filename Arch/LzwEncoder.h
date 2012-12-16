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
	~LzwEncoder();
	void WriteStartInfo(char* fileName);
	void Encode();

private:
	int ReadNextByte();
	void AddNewNode(byte symbol, unsigned int hashCode);
	unsigned long GetInputFileSize();

	FILE* _inputFile;
	BitsWriter* _bitsWriter;
	HashTree _hashTree;
	unsigned int _parent;
	unsigned long _inputFileSize;
};

#endif