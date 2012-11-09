#ifndef H_LZW_DECODER
#define H_LZW_DECODER

#include "stdio.h"
#include "Common.h"
#include "HashTree.h"
#include "BitsReader.h"
#include "TList.h"

class LzwDecoder
{
public:
	LzwDecoder(FILE* inputFile, FILE* outputFile);
	~LzwDecoder();
	void Decode();

private:
	TList<byte>* GetReversedStringByCode(int code);
	void WriteOutput(TList<byte>* symbols);
	void WriteOutput(byte code);
	void AddNewNode(byte symbolCode, unsigned int hashCode);

	FILE* _outputFile;
	BitsReader* _bitsReader;
	HashTree _hashTree;
	unsigned int _parent;
};

#endif