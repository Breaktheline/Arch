#include "BinaryFileOperations.h"

BinaryFileOperations::BinaryFileOperations(FILE* file)
{
	_file = file;
	_buffer = 0;
	_bufferSize = 0;
	_bitsInCode = MIN_CODE_LEN;
	_codeSize = pow(2.0, _bitsInCode - 1);
}

BinaryFileOperations::~BinaryFileOperations()
{
	fclose(_file);
}

void BinaryFileOperations::ChangeCodeLength(int code)
{
	while (code >= _codeSize && _bitsInCode < MAX_CODE_LEN)
	{
		_bitsInCode++;
		_codeSize = pow(2.0, _bitsInCode - 1);
	}
}

