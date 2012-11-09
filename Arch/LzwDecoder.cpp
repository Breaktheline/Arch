#include "LzwDecoder.h"

LzwDecoder::LzwDecoder(FILE* inputFile, FILE* outputFile)
{
	_outputFile = outputFile;
	_bitsReader = new BitsReader(inputFile);
}

LzwDecoder::~LzwDecoder()
{
	fclose(_outputFile);
	delete _bitsReader;
}

void LzwDecoder::Decode()
{
	int code = _bitsReader->ReadNextBits();
	
	if (code != NIL)
	{
		WriteOutput(code);
		_parent = code;
	}

	while(code != NIL)
	{
		code = _bitsReader->ReadNextBits();
		if (code == NIL)
		{
			break;
		}

		//Получаем закодированную строку и записываем ее в файл.
		TList<byte>* symbols = GetReversedStringByCode(code);
		WriteOutput(symbols);
		//Первый символ строки.
		byte symbolCode = symbols->GetLast();

		delete symbols;

		unsigned int hashCode = _hashTree.GetHash(symbolCode, _parent);
		int index = _hashTree.FindNodeIndex(symbolCode, _parent, hashCode);

		//Если строки еще нет, то добавляем.
		if (index == NIL)
		{
			AddNewNode(symbolCode, hashCode);
		}

		//родителем является последний символ закодированной строки.
		_parent = code;
	}

}

//Возвращает строку, представленную кодом в обратном порядке.
TList<byte>* LzwDecoder::GetReversedStringByCode(int code)
{
	TList<byte>* symbols = new TList<byte>();

	//Если это код единственного символа.
	if (code < CHARS_COUNT)
	{
		symbols->Add(code);
		return symbols;
	}

	Node* node = _hashTree.FindNode(code);

	//Пока не дойдем до конца строки.
	while(node->parent != NIL)
	{
		symbols->Add(node->symbol);
		node = _hashTree.FindNode(node->parent);
	}

	symbols->Add(node->symbol);

	return symbols;
}

void LzwDecoder::WriteOutput(TList<byte>* symbols)
{
	int count = symbols->GetCount();

	for(int i = count - 1; i >= 0; i--)
	{
		WriteOutput(symbols->GetElement(i));
	}
}

void LzwDecoder::WriteOutput(byte code)
{
	fputc(code, _outputFile);
}

void LzwDecoder::AddNewNode(byte symbolCode, unsigned int hashCode)
{
	Node* node = _hashTree.AddNode(symbolCode, _parent, hashCode);
	if (node == NULL)
	{
		_hashTree.Clear();
		if (_parent < CHARS_COUNT)
		{
			node = _hashTree.AddNode(symbolCode, _parent, hashCode);
		}
	}
}
