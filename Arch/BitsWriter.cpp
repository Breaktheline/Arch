#include "BitsWriter.h"

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
			fputc(_buffer, _file);
			_bufferSize = 0;
			_buffer = 0;
		}
	}

	//Увеличиваем длину кода, если индекс в таблице возрос.
	ChangeCodeLength(code);
}

void BitsWriter::WriteReminder()
{
	if (_bufferSize > 0)
	{
		fputc(_buffer, _file);
	}
}

