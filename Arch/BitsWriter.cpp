#include "BitsWriter.h"

void BitsWriter::AddBitsToBuffer(int code)
{
	//��������� �� ������ ���� � ���������� � ����, ����� ���������� ����.
	for(int shift = _bitsInCode; shift > 0; shift--)
	{
		//������� ���������� ��� �����.
		byte bit = (code >> (shift - 1)) & 1;
		bit <<= 7 - _bufferSize;
		//��������� ��� � �����.
		_buffer |= bit;
		_bufferSize++;
		//���� ����� ��������, �� ����� � ����.
		if (_bufferSize == 8)
		{
			fputc(_buffer, _file);
			_bufferSize = 0;
			_buffer = 0;
		}
	}

	//����������� ����� ����, ���� ������ � ������� ������.
	ChangeCodeLength(code);
}

void BitsWriter::WriteReminder()
{
	if (_bufferSize > 0)
	{
		fputc(_buffer, _file);
	}
}

