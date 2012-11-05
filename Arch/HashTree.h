#ifndef H_HASH_TREE
#define H_HASH_TREE

#define MIN_CODE_LEN 9
#define MAX_CODE_LEN 15
#define CHARS_COUNT 256
#define HASH_SIZE 65536
typedef unsigned char byte;

#include <stdlib.h>

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
		return index == -1 && parent == -1;
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
	Node* GetNode(byte suffixChar, int parentCode = -1);
private:
	unsigned int GetHash(byte suffixChar, int parentCode);

	Node** _nodes;
};

#endif