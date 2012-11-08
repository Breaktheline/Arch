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
		
		//≈сли строки не существует в таблице, то добавл€ем.
		if (nodeIndex == NIL)
		{
			AddNewNode(symbol, hashCode);
		}
		//≈сли строка в таблице есть, мен€ем родител€ на код строки.
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

	//≈сли таблица заполнена, очищаем, добавл€ем строку, если состоит из 2 символов.
	if (node == NULL)
	{
		_hashTree.Clear();
		if (_parent < CHARS_COUNT)
		{
			node = _hashTree.AddNode(symbol, _parent, hashCode);
		}
	}

	//в файл выводитс€ код символа родител€.
	_bitsWriter->AddBitsToBuffer(_parent);
	_parent = symbol;
}


