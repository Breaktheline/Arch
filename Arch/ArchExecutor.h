#ifndef H_ARCH_EXECUTOR
#define H_ARCH_EXECUTOR

#include "Options.h"
#include "CrcMaker.h"

class ArchExecutor
{
public:
	void Execute(Options* options);

	void CheckFileIntagrity( Options* options );

	bool CheckCrc(FILE* file);

private:
	unsigned long ReadCrcFromFile(FILE* file);
	unsigned long ReadUncompressedSize(FILE* file);
	unsigned long MakeCrc(FILE* file);

	unsigned long GetLastFilePosition( FILE* file );

	unsigned int ReadToBuffer(byte* buffer, FILE* file);

	CrcMaker _crcMaker;
	unsigned long _uncompressedFileSize;
};

#endif


