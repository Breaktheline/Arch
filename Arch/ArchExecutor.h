#ifndef H_ARCH_EXECUTOR
#define H_ARCH_EXECUTOR

#include "Options.h"
#include "CrcMaker.h"

class ArchExecutor
{
public:
	void Execute(Options* options);

private:
	void CheckFileIntagrity(Options* options);
	bool CheckCrc(FILE* file);
	void EncodeFiles(Options* options);
	void EncodeFilesToStdout(Options* options);

	unsigned long ReadCrcFromFile(FILE* file);
	unsigned long ReadUncompressedSize(FILE* file);
	unsigned long MakeCrc(FILE* file);

	unsigned long GetLastFilePosition(FILE* file);

	unsigned int ReadToBuffer(byte* buffer, FILE* file);
	void ListCompressionInfo(Options* options);
	void OutputCompressInfo(FILE* file );

	char* ReadFileName(FILE* file);
	void FillFilesFromDir (TList<char*>* files, const char* dirNAme);
	char* GetName(char* path);
	bool IsCompressedFile(FILE* file);
	char* GetNameForDecompressedFile(char* path);
	void DecodeFiles(Options* options);
	char* GetFilePath( char* path );
	CrcMaker _crcMaker;
	unsigned long _uncompressedFileSize;
};

#endif


