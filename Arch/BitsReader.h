#ifndef H_BITS_READER
#define H_BITS_READER

#include "Common.h"
#include "BinaryFileOperations.h"

class BitsReader: BinaryFileOperations
{
public:
	BitsReader(FILE* inputFile);
	int ReadNextBits();

private:
	bool CanReadFile();

	long _lastFilePosition;
};

#endif
