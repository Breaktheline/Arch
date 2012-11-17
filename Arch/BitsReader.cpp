#include "BitsReader.h"

BitsReader::BitsReader(FILE* inputFile) : BinaryFileOperations(inputFile)
{
	ReadFileInfo();
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

unsigned long BitsReader::MakeCrc()
{
	int nextByte;
	unsigned long crc = 0L;
	byte buffer[CRC_BUFFER_SIZE];
	int bufferLength;

	SetFileToStart();
	while((bufferLength = ReadToBuffer(buffer)) > 0)
	{
		//TODO: если длина файла больше long, то нужна другая проверка.
		if (ftell(_file) == _lastFilePosition)
		{
			bufferLength -= CRC_SIZE_BYTES + FILE_SIZE_BYTES;
		}

		crc = _crcMaker.UpdateCrc(crc, buffer, bufferLength);
	}

	SetFileToStart();

	return crc;
}

bool BitsReader::CheckCrc()
{
	return _crc == MakeCrc();
}

void BitsReader::SetFileToStart()
{
	// Установить позицию файла на начало.
	rewind(_file);
}

unsigned int BitsReader::ReadToBuffer(byte* buffer)
{
	return fread(buffer, sizeof(byte), CRC_BUFFER_SIZE, _file);
}

void BitsReader::ReadFileInfo()
{
	fseek(_file, -CRC_SIZE_BYTES-FILE_SIZE_BYTES, SEEK_END);
	fread(&_crc, CRC_SIZE_BYTES, 1, _file);
	fread(&_uncompressedFileSize, FILE_SIZE_BYTES, 1, _file);
	_lastFilePosition = ftell(_file);
	SetFileToStart();
}

bool BitsReader::CanReadFile()
{
	return ftell(_file) <= _lastFilePosition - CRC_SIZE_BYTES - FILE_SIZE_BYTES;
}

unsigned long BitsReader::GetUncompressedSize()
{
	return _uncompressedFileSize;
}

