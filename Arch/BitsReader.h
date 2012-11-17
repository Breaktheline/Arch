#ifndef H_BITS_READER
#define H_BITS_READER

#include "Common.h"
#include "BinaryFileOperations.h"

class BitsReader: BinaryFileOperations
{
public:
	BitsReader(FILE* inputFile);
	int ReadNextBits();

	bool CanReadFile();

	bool CheckCrc();

private:
	void ReadFileInfo();
	unsigned long MakeCrc();

	unsigned int ReadToBuffer(byte* buffer);
	void SetFileToStart();
	void ReadUncompFileSize();
	void ReadCrc();

	unsigned long _uncompressedFileSize;
	long _lastFilePosition;
};

#endif
