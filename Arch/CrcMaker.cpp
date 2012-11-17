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



unsigned long CrcMaker::UpdateCrc(unsigned long crc, unsigned char *buf, int len)
{
	unsigned long c = crc ^ 0xffffffffL;

	for (int n = 0; n < len; n++) 
	{
		c = _crcTable[(c ^ buf[n]) & 0xff] ^ (c >> 8);
	}

	return c ^ 0xffffffffL;
}
