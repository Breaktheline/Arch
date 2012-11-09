#include "BitsReader.h"

int BitsReader::ReadNextBits()
{
	int code = 0;
	for(int shift = _bitsInCode; shift > 0; shift--)
	{
		if (_bufferSize == 0)
		{
			_buffer = fgetc(_file);
			if (_buffer == EOF)
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
