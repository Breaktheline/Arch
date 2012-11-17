#ifndef H_CRC_MAKER
#define H_CRC_MAKER

#include "Common.h"

class CrcMaker
{
public:
	CrcMaker();
	unsigned long UpdateCrc(unsigned long crc, unsigned char *buf, int len);

private:
	unsigned long _crcTable[256];
};

#endif