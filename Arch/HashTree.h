#ifndef H_HASH_TREE
#define H_HASH_TREE

#define CHARS_COUNT 256
#define HASH_SIZE 65536

#include "Common.h"

struct Node
{
	Node()
	{
		symbol = 0;
	};

	Node(int aParent, int aIndex, byte aSymbol)
	{
		symbol = aSymbol;
		parent = aParent;
		index = aIndex;
	};

	bool IsEmpty()
	{
		return index == NIL && parent == NIL;
	}

	bool IsEqual(byte symbolCode, int parentCode)
	{
		return this->parent == parentCode && this->symbol == symbolCode;
	}

	int parent;
	int index;
	byte symbol;
};

class HashTree
{
public:
	HashTree();
	~HashTree();
	unsigned int GetHash(byte symbolCode, unsigned int parentCode);
	//���������� NULL, ���� ���� ���.
	Node* FindNode(unsigned int index);

	//���������� NIL, ���� ���� ���.
	int FindNodeIndex(byte symbolCode, unsigned int parentCode, unsigned int hashCode);

	//���������� NULL, ���� ������� ���������.
	Node* AddNode(byte symbolCode, int parentCode, unsigned int hashCode);
	void Clear();
private:

	Node** _nodes;
};

#endif