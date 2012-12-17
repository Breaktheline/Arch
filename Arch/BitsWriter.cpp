#include "BitsWriter.h"

BitsWriter::BitsWriter(FILE* outputFile) : BinaryFileOperations(outputFile)
{
	_crcBufferSize = 0;
	_crc = 0L;
}

void BitsWriter::AddBitsToBuffer(int code)
{
	//Добавляем по одному биту и записываем в файл, когда наполнится байт.
	for(int shift = _bitsInCode; shift > 0; shift--)
	{
		//достаем конкретный бит числа.
		byte bit = (code >> (shift - 1)) & 1;
		bit <<= 7 - _bufferSize;
		//добавляем бит в буфер.
		_buffer |= bit;
		_bufferSize++;
		//если буфер заполнет, то пишем в файл.
		if (_bufferSize == 8)
		{
			WriteByte();
			if (_crcBufferSize == CRC_BUFFER_SIZE)
			{
				UpdateCrc();
			}
		}
	}

	//Увеличиваем длину кода, если индекс в таблице возрос.
	ChangeCodeLength(code);
}

void BitsWriter::WriteByte() 
{
	fputc(_buffer, _file);
	_crcBuffer[_crcBufferSize] = _buffer;
	_crcBufferSize++;

	_bufferSize = 0;
	_buffer = 0;
}

void BitsWriter::WriteEndOfFile(unsigned long uncompSize)
{
	if (_bufferSize > 0)
	{
		WriteByte();
		UpdateCrc();
	}

	fwrite(&_crc, CRC_SIZE_BYTES, 1, _file);
	fwrite(&uncompSize, FILE_SIZE_BYTES, 1, _file);
}

void BitsWriter::UpdateCrc()
{
	_crc = _crcMaker.UpdateCrc(_crc, _crcBuffer, _crcBufferSize);
	_crcBufferSize = 0;
}

void BitsWriter::WriteBeginOfFile()
{
	byte id1 = ID1;
	byte id2 = ID2;
	_buffer = id1;
	WriteByte();
	_buffer = id2;
	WriteByte();
}