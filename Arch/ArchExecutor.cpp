#include "ArchExecutor.h"

void ArchExecutor::Execute(Options* options)
{
	if (options->Test)
	{
		CheckFileIntagrity(options);
	}
}

unsigned long ArchExecutor::ReadCrcFromFile(FILE* file)
{
	fseek(file, -CRC_SIZE_BYTES-FILE_SIZE_BYTES, SEEK_END);
	unsigned long crc;
	fread(&crc, CRC_SIZE_BYTES, 1, file);
	rewind(file);
	return crc;
}

unsigned long ArchExecutor::MakeCrc(FILE* file)
{
	int nextByte;
	unsigned long crc = 0L;
	byte buffer[CRC_BUFFER_SIZE];
	int bufferLength;

	long lastPosition = GetLastFilePosition(file);

	while((bufferLength = ReadToBuffer(buffer, file)) > 0)
	{
		//TODO: если длина файла больше long, то нужна друга€ проверка.
		if (ftell(file) == lastPosition)
		{
			bufferLength -= CRC_SIZE_BYTES + FILE_SIZE_BYTES;
		}

		crc = _crcMaker.UpdateCrc(crc, buffer, bufferLength);
	}

	rewind(file);

	return crc;
}

bool ArchExecutor::CheckCrc( FILE* file )
{
	return ReadCrcFromFile(file) == MakeCrc(file);
}

unsigned int ArchExecutor::ReadToBuffer( byte* buffer, FILE* file )
{
	return fread(buffer, sizeof(byte), CRC_BUFFER_SIZE, file);
}

unsigned long ArchExecutor::ReadUncompressedSize( FILE* file )
{
	fseek(file, -FILE_SIZE_BYTES, SEEK_END);
	unsigned long size;
	fread(&size, FILE_SIZE_BYTES, 1, file);
	rewind(file);

	return size;
}

unsigned long ArchExecutor::GetLastFilePosition(FILE* file)
{
	fseek(file, 0, SEEK_END);
	long lastFilePosition = ftell(file);
	rewind(file);
	return lastFilePosition;
}

void ArchExecutor::CheckFileIntagrity(Options* options)
{
	int filesCount = options->Files->GetCount();
	for(int i = 0; i < filesCount; i++)
	{
		FILE* file = fopen(options->Files->GetElement(i), "rb");
		if (!CheckCrc(file))
		{
			printf("invalid compressed data--crc error\n");
		}
		fclose(file);
	}
}
