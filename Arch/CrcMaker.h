#ifndef H_CRC_MAKER
#define H_CRC_MAKER

#include "Common.h"

class CrcMaker
{
public:
	static const int BUFFER_SIZE = 1024;
	CrcMaker();
	unsigned long MakeCrc(char* fileName);
	void WriteCrcToFile(char* fileName);
	unsigned long ReadCrcFromFile(char* fileName);

private:
	unsigned long _crcTable[256];
	unsigned long UpdateCrc(unsigned long crc, unsigned char *buf, int len);

};

#endif