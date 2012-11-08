#ifndef H_BITS_WRITER
#define H_BITS_WRITER

#include "Common.h"

class BitsWriter
{
public:
	BitsWriter(FILE* outputFile);
	void AddBitsToBuffer(int bits);
	void WriteReminder();
private:
	void ChangeCodeLength(int nodeIndex);

	FILE* _outputFile;
	byte _buffer;
	int _bufferSize;
	int _bitsInCode;
	int _codeSize;
};

#endif
