#include "HashTree.h"

HashTree::HashTree()
{
	_nodes = new Node*[HASH_SIZE];
	for (int i = 0; i < CHARS_COUNT; i++)
	{
		_nodes[i] = new Node(-1, i, i);
	}

	for (int i = CHARS_COUNT; i < HASH_SIZE; i++)
	{
		_nodes[i] = NULL;
	}
}

unsigned int HashTree::GetHash(byte symbolCode, unsigned int parentCode)
{
	unsigned int key = parentCode << 1;
	key ^= symbolCode;
	key &= HASH_SIZE - 1;
	return key;
}

Node* HashTree::FindNode(unsigned int index)
{
	return _nodes[index];
}

int HashTree::FindNodeIndex(byte symbolCode, unsigned int parentCode, unsigned int hashCode)
{
	Node* node = _nodes[hashCode];

	//���� ������ �����, �� ���������� NIL.
	if (node == NULL)
	{
		return NIL;
	}

	//���� ������ �� ����� � �� ����� ������� ����
	if (node->IsEqual(symbolCode, parentCode))
	{
		return hashCode;
	}

	//���� ������ �� �����, �� � ��� ���������� ������ ����, �� ���� ������ ������ ��� ������ ������
	for(int index = hashCode + 1; index < HASH_SIZE; index++)
	{
		//���� �� ������ � ������������������ ����� ������� 0-255, �� ���������� ������ �� 256.
		if (index < CHARS_COUNT)
		{
			index = CHARS_COUNT;
		}

		//���� ����� ������ ������.
		if (_nodes[index] == NULL)
		{
			return NIL;
		}

		//���� ����� ������ ������, �� ���������� �� ������.
		if (_nodes[index]->IsEqual(symbolCode, parentCode))
		{
			return index;
		}

		//���� ����� �� ����� �������, �� �������� ������ � ������.
		if (index == HASH_SIZE - 1)
		{
			index = 0;
		}

		//���� �� ������ ��� ������� � �� ����� ���������� �����.
		if (index == hashCode)
		{
			break;
		}
	}

	return NIL;
}

Node* HashTree::AddNode(byte symbolCode, int parentCode, unsigned int hashCode)
{
	Node* node = _nodes[hashCode];

	//���� ������ �����, �� ��������� ����� ����
	if (node == NULL)
	{
		_nodes[hashCode] = new Node(parentCode, hashCode, symbolCode);
		return _nodes[hashCode];
	}

	//���� ������ �� �����, �� � ��� ���������� ������ ����, �� ���� ������ ������ ������
	for(int index = hashCode + 1; index < HASH_SIZE; index++)
	{
		//���� �� ������ � ������������������ ����� ������� 0-255, �� ���������� ������ �� 256.
		if (index < CHARS_COUNT)
		{
			index = CHARS_COUNT;
		}

		//���� ����� ������ ������.
		if (_nodes[index] == NULL)
		{
			_nodes[index] = new Node(parentCode, hashCode, symbolCode);
			return _nodes[index];
		}

		//���� ����� �� ����� �������, �� �������� ������ � ������.
		if (index == HASH_SIZE - 1)
		{
			index = 0;
		}

		//���� �� ������ ��� ������� � �� ����� ���������� �����.
		if (index == hashCode)
		{
			break;
		}
	}

	//���� ������ ��������, ���������� NULL
	return NULL;
}

HashTree::~HashTree()
{
	for(int i = 0; i < HASH_SIZE; i++)
	{
		if (_nodes[i] != NULL)
		{
			delete _nodes[i];
		}
	}

	delete _nodes;
}

void HashTree::Clear()
{
	for(int i = CHARS_COUNT; i < HASH_SIZE; i++)
	{
		if (_nodes[i] != NULL)
		{
			delete _nodes[i];
		}
		_nodes[i] = NULL;
	}
}

