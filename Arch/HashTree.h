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

struct GetNodeResult
{
	bool exists;
	int pointer;
};

class HashTree
{
public:
	HashTree();
	~HashTree();
	unsigned int GetHash(byte symbolCode, int parentCode);
	//возвращает NIL, если узла нет.
	int FindNodeIndex(byte symbolCode, int parentCode, unsigned int hashCode);
	//возвращает NULL, если таблица заполнена.
	Node* AddNode(byte symbolCode, int parentCode, unsigned int hashCode);
	void Clear();
private:


	Node** _nodes;
};

#endif