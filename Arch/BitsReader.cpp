#include "BitsReader.h"

BitsReader::BitsReader(FILE* inputFile) : BinaryFileOperations(inputFile)
{
	fseek(inputFile, 0, SEEK_END);
	_lastFilePosition = ftell(inputFile);
	rewind(inputFile);
}

int BitsReader::ReadNextBits()
{
	int code = 0;
	for(int shift = _bitsInCode; shift > 0; shift--)
	{
		if (_bufferSize == 0)
		{
			_buffer = fgetc(_file);
			//TODO: если длина файла больше long
			if (_buffer == EOF || !CanReadFile())
			{
				return NIL;
			}
			_bufferSize = 8;
		}
		int bit = (_buffer >> (_bufferSize - 1)) & 1;
		bit <<= shift - 1;
		code |= bit;
		_bufferSize--;
	}

	ChangeCodeLength(code);

	return code;
}

bool BitsReader::CanReadFile()
{
	return ftell(_file) <= _lastFilePosition - CRC_SIZE_BYTES - FILE_SIZE_BYTES;
}

void BitsReader::SetStart()
{
	fseek(_file, 2, SEEK_SET);
	char b;
	int i = 0;
	while ((b = fgetc(_file)) != '\0')
	{
		i++;
	}
}