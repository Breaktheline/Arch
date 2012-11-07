#include "LzwEncoder.h"

LzwEncoder::LzwEncoder()
{
	_bitsInCode = MIN_CODE_LEN;
	_codeSize = pow(2.0, _bitsInCode);
}

void LzwEncoder::Encode(const char* inputFileName, const char* outputFileName)
{
	FILE* inputFile = fopen(inputFileName, "rb");
	if (inputFile == NULL)
	{
		printf("Can't open file %s", inputFileName);
		return;
	}

	FILE* outputFile = fopen(outputFileName, "wb");
	if (outputFile == NULL)
	{
		printf("Can't open file %s", outputFile);
		return;
	}

	_parent = ReadNextByte(inputFile);
	
	while (!feof(inputFile))
	{
		byte symbol = ReadNextByte(inputFile);
		if (symbol == EOF)
		{
			break;
		}

		unsigned char hashCode = _hashTree.GetHash(symbol, _parent);
		int nodeIndex = _hashTree.FindNodeIndex(symbol, _parent, hashCode);
		
		//���� ������ �� ���������� � �������, �� ���������.
		if (nodeIndex == NIL)
		{
			AddNewNode(symbol, hashCode, outputFile);
		}
		//���� ������ � ������� ����, ������ �������� �� ��� ������.
		else
		{
			ChangeCodeLength(nodeIndex);
			_parent = nodeIndex;
		}
	}
}

byte LzwEncoder::ReadNextByte(FILE* inputFile)
{
	byte next;
	read(inputFile, &next, sizeof(next));

	return next;
}

void LzwEncoder::WriteCode(FILE* outputFile, int code)
{
	//TODO
}

void LzwEncoder::AddNewNode(byte symbol, unsigned char hashCode, FILE* outputFile)
{
	Node* node = _hashTree.AddNode(symbol, _parent, hashCode);

	//���� ������� ���������, �������, ��������� ������, ���� ������� �� 2 ��������.
	if (node == NULL)
	{
		_hashTree.Clear();
		if (_parent < CHARS_COUNT)
		{
			node = _hashTree.AddNode(symbol, _parent, hashCode);
		}
	}

	//� ���� ��������� ��� ������� ��������.
	WriteCode(outputFile, _parent);
	_parent = symbol;
}

void LzwEncoder::ChangeCodeLength(int nodeIndex)
{
	//����������� ����� ����, ���� ������ � ������� ������.
	if (nodeIndex >= _codeSize )
	{
		_bitsInCode++;
		_codeSize = pow(2.0, _bitsInCode);
	}
}
