#include "BitsWriter.h"

BitsWriter::BitsWriter(FILE* outputFile)
{
	_outputFile = outputFile;
	_buffer = 0;
	_bufferSize = 0;
	_bitsInCode = MIN_CODE_LEN;
	_codeSize = pow(2.0, _bitsInCode);
}

void BitsWriter::AddBitsToBuffer(int nodeIndex)
{
	//����������� ����� ����, ���� ������ � ������� ������.
	while (nodeIndex >= _codeSize)
	{
		_bitsInCode++;
		_codeSize = pow(2.0, _bitsInCode);
	}

	//��������� �� ������ ���� � ���������� � ����, ����� ���������� ����.
	for (int shift = _bitsInCode; shift > 0; shift--)
	{
		//������� ���������� ��� �����.
		byte bit = (nodeIndex >> (shift - 1)) & 1;
		bit <<= 7 - _bufferSize;
		//��������� ��� � �����.
		_buffer |= bit;
		_bufferSize++;
		if (_bufferSize == 8)
		{
			fputc(_buffer, _outputFile);
			_bufferSize = 0;
			_buffer = 0;
		}
	}
}

void BitsWriter::WriteReminder()
{
	if (_bufferSize > 0)
	{
		fputc(_buffer, _outputFile);
	}
}

BitsWriter::~BitsWriter()
{
	fclose(_outputFile);
}
