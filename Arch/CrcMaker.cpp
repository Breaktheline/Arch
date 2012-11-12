#include "CrcMaker.h"

CrcMaker::CrcMaker()
{
	for (int i = 0; i < 256; i++) 
	{
		unsigned long crc = i;

		for (int j = 0; j < 8; j++) 
		{
			if (crc & 1) 
			{
				crc = 0xedb88320L ^ (crc >> 1);
			} 
			else 
			{
				crc = crc >> 1;
			}
		}

		_crcTable[i] = crc;
	}
}

unsigned long CrcMaker::MakeCrc(char* fileName)
{
	FILE* file = fopen(fileName, "rb");
	if (file == NULL)
	{
		throw FileException(ErrorMessages::FILE_OPEN_ERROR, fileName);
	}

	int nextByte;
	unsigned long crc = 0L;
	byte buffer[BUFFER_SIZE];
	while(int bufferLength = (fread(&buffer, sizeof(byte), BUFFER_SIZE, file)) > 0)
	{
		UpdateCrc(crc, buffer, bufferLength);
	}
}

unsigned long CrcMaker::UpdateCrc(unsigned long crc, unsigned char *buf, int len)
{
	unsigned long c = crc ^ 0xffffffffL;

	for (int n = 0; n < len; n++) 
	{
		c = _crcTable[(c ^ buf[n]) & 0xff] ^ (c >> 8);
	}

	return c ^ 0xffffffffL;
}

void CrcMaker::WriteCrcToFile(char* fileName)
{
	//TODO: записать в файл CRC32
}

unsigned long CrcMaker::ReadCrcFromFile(char* fileName)
{
	//TODO: вытащить из файла CRC32
	return 0;
}
