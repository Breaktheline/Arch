#include "LzwEncoder.h"


void LzwEncoder::Encode(const char* inputFileName, const char* outputFileName)
{
	FILE* inputFile = fopen(inputFileName, "r");
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

	int parent = NIL;
	while (!feof(inputFile))
	{
		byte symbol = ReadNextByte(inputFile);
		unsigned char hashCode = hashTree.GetHash(symbol, parent);

		int nodeIndex = hashTree.FindNodeIndex(symbol, parent, hashCode);
		
		//���� ������ �� ���������� � �������.
		if (nodeIndex == NIL)
		{
			Node* node = hashTree.AddNode(symbol, parent, hashCode);

			//���� ������� ���������, �������, ������� ������ ��� ��������.
			if (node == NULL)
			{
				//TODO:
				hashTree.Clear();
				parent = NIL;
				node = hashTree.AddNode(symbol, parent, hashCode);
			}

			parent = symbol;
		}
		//���� ������ � ������� ����.
		else
		{
			parent = nodeIndex;
		}

	}

}

byte LzwEncoder::ReadNextByte(FILE* inputFile)
{
	//TODO
	return 1;
}
