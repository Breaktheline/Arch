#include "LzwEncoder.h"

LzwEncoder::LzwEncoder(FILE* inputFile, FILE* outputFile)
{
	_inputFile = inputFile;
	_bitsWriter = new BitsWriter(outputFile);
}

LzwEncoder::~LzwEncoder()
{
	fclose(_inputFile);
	delete _bitsWriter;
}

void LzwEncoder::Encode()
{
	_parent = ReadNextByte();

	while (!feof(_inputFile))
	{
		byte symbol = ReadNextByte();

		//Ищем новую строку
		unsigned int hashCode = _hashTree.GetHash(symbol, _parent);
		int nodeIndex = _hashTree.FindNodeIndex(symbol, _parent, hashCode);
		
		//Если строки не существует в таблице, то добавляем.
		if (nodeIndex == NIL)
		{
			AddNewNode(symbol, hashCode);
		}
		//Если строка в таблице есть, меняем родителя на код строки.
		else
		{
			_parent = nodeIndex;
		}
	}

	_bitsWriter->WriteReminder();
}

int LzwEncoder::ReadNextByte()
{
	return fgetc(_inputFile);
}

void LzwEncoder::AddNewNode(byte symbol, unsigned int hashCode)
{
	Node* node = _hashTree.AddNode(symbol, _parent, hashCode);

	//Если таблица заполнена, очищаем, добавляем строку, если состоит из 2 символов.
	if (node == NULL)
	{
		_hashTree.Clear();
		if (_parent < CHARS_COUNT)
		{
			node = _hashTree.AddNode(symbol, _parent, hashCode);
		}
	}

	//в файл выводится код символа родителя.
	_bitsWriter->AddBitsToBuffer(_parent);
	_parent = symbol;
}
