#ifndef H_BINARY_FILE_OPERATIONS
#define H_BINARY_FILE_OPERATIONS

#include "Common.h"
#include "CrcMaker.h"

class BinaryFileOperations
{
public:
	BinaryFileOperations(FILE* file);
	~BinaryFileOperations();
protected:
	void ChangeCodeLength(int nodeIndex);

	FILE* _file;
	int _buffer;
	int _bufferSize;
	int _bitsInCode;
	int _codeSize;


};

#endif
