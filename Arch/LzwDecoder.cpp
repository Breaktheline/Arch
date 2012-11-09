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
	//TODO: Записать строку
	_parent = code;

	while(code != NIL)
	{
		code = _bitsReader->ReadNextBits();
		if (code == NIL)
		{
			//TODO:
		}

		byte symbolCode = GetNextSymbol(code);
		unsigned int hashCode = _hashTree.GetHash(symbolCode, _parent);
		int index = _hashTree.FindNodeIndex(symbolCode, _parent, hashCode);
		if (index == NIL)
		{
			Node* node = _hashTree.AddNode(symbolCode, _parent, hashCode);
			if (node == NULL)
			{
				//TODO: clear
			}
			_parent = symbolCode;
		}
	}


}

byte LzwDecoder::GetNextSymbol(int code)
{
	if (code < CHARS_COUNT)
	{
		return code;
	}

	//TODO:
}
