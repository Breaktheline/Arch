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

unsigned int HashTree::GetHash(byte suffixChar, int parentCode)
{
	unsigned int key = parentCode << 5;
	key ^= suffixChar;
	key &= HASH_SIZE - 1;
	return key;
}

Node* HashTree::GetNode(byte symbolCode, int parentCode)
{
	//если ищем единственный символ, то он точно есть
	if (parentCode == -1)
	{
		return _nodes[symbolCode];
	}

	//находим хэш-код, соответсвующий строке
	unsigned int hashCode = GetHash(symbolCode, parentCode);
	Node* node = _nodes[hashCode];

	//если ячейка пуста, то добавляем новый узел
	if (node == NULL)
	{
		_nodes[hashCode] = new Node(parentCode, hashCode, symbolCode);
		return _nodes[hashCode];
	}

	//Если ячейка не пуста и мы нашли искомый узел
	if (node->IsEqual(symbolCode, parentCode))
	{
		return _nodes[hashCode];
	}

	//Если ячейка не пуста, но в ней содержится другой узел, то ищем первую пустую или равную ячейку
	for(int index = hashCode + 1; index < HASH_SIZE; index++)
	{

		//Если мы попали в инициализированную часть таблицы 0-255, то увеличивем индекс до 256.
		if (index < CHARS_COUNT)
		{
			index = CHARS_COUNT;
		}

		//Если нашли пустую ячейку.
		if (_nodes[index] == NULL)
		{
			_nodes[index] = new Node(parentCode, hashCode, symbolCode);
			return _nodes[index];
		}

		// Если нашли равную ячейку, то возвращаем ее.
		if (_nodes[index]->IsEqual(symbolCode, parentCode))
		{
			return _nodes[index];
		}

		//Если дошли до конца таблицы, то начинаем искать с начала.
		if (index == HASH_SIZE - 1)
		{
			index = 0;
		}

		//Если мы прошли всю таблицу и не нашли свободного места.
		if (index == hashCode)
		{
			break;
		}
	}

	//Если некуда вставить, возвращаем NULL
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
