#ifndef H_BITS_WRITER
#define H_BITS_WRITER

#include "Common.h"
#include "BinaryFileOperations.h"

class BitsWriter: BinaryFileOperations
{
public:
	BitsWriter(FILE* outputFile);

	void AddBitsToBuffer(int bits);
	void WriteEndOfFile(unsigned long uncompSize);
	void WriteBeginOfFile(char* inputFileName);

private:
	void WriteByte();
	void UpdateCrc();

	byte _crcBuffer[CRC_BUFFER_SIZE];
	int _crcBufferSize;
	CrcMaker _crcMaker;
	unsigned long _crc;
};

#endif
