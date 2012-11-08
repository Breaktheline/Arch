#include "LzwEncoder.h"

LzwEncoder::LzwEncoder(FILE* inputFile, FILE* outputFile)
{
	_inputFile = inputFile;
	_bitsWriter = new BitsWriter(outputFile);
}

void LzwEncoder::Encode()
{
	_parent = ReadNextByte();
	
	while (!feof(_inputFile))
	{
		byte symbol = ReadNextByte();
		if (symbol == EOF)
		{
			break;
		}

		unsigned char hashCode = _hashTree.GetHash(symbol, _parent);
		int nodeIndex = _hashTree.FindNodeIndex(symbol, _parent, hashCode);
		
		//���� ������ �� ���������� � �������, �� ���������.
		if (nodeIndex == NIL)
		{
			AddNewNode(symbol, hashCode);
		}
		//���� ������ � ������� ����, ������ �������� �� ��� ������.
		else
		{
			_parent = nodeIndex;
		}
	}
}

byte LzwEncoder::ReadNextByte()
{
	byte next;
	fread(&next, 1, 1, _inputFile);

	return next;
}

void LzwEncoder::AddNewNode(byte symbol, unsigned char hashCode)
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
	_bitsWriter->AddBitsToBuffer(_parent);
	_parent = symbol;
}


