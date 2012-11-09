#ifndef H_BITS_WRITER
#define H_BITS_WRITER

#include "Common.h"
#include "BinaryFileOperations.h"

class BitsWriter: BinaryFileOperations
{
public:
	BitsWriter(FILE* outputFile): BinaryFileOperations(outputFile) {};
	void AddBitsToBuffer(int bits);
	void WriteReminder();
};

#endif
