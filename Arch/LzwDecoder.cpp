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

		//�������� �������������� ������ � ���������� �� � ����.
		TList<byte>* symbols = GetReversedStringByCode(code);
		WriteOutput(symbols);
		//������ ������ ������.
		byte symbolCode = symbols->GetLast();

		delete symbols;

		unsigned int hashCode = _hashTree.GetHash(symbolCode, _parent);
		int index = _hashTree.FindNodeIndex(symbolCode, _parent, hashCode);

		//���� ������ ��� ���, �� ���������.
		if (index == NIL)
		{
			AddNewNode(symbolCode, hashCode);
		}

		//��������� �������� ��������� ������ �������������� ������.
		_parent = code;
	}

}

//���������� ������, �������������� ����� � �������� �������.
TList<byte>* LzwDecoder::GetReversedStringByCode(int code)
{
	TList<byte>* symbols = new TList<byte>();

	//���� ��� ��� ������������� �������.
	if (code < CHARS_COUNT)
	{
		symbols->Add(code);
		return symbols;
	}

	Node* node = _hashTree.FindNode(code);

	//���� �� ������ �� ����� ������.
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
