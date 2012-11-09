#ifndef H_TLIST
#define H_TLIST

#include "Common.h"

template <class T> class TList
{
public:
	TList()
	{
		_count = 0;
		_capacity = 0;
		_elements = NULL;
	};

	TList(T* elements, int length)
	{
		_count = length;
		_capacity = length;
		_elements = elements;
	};

	~TList()
	{
		if (_elements != NULL)
		{
			free(_elements);
		}
	};

	void Clear()
	{
		if (_elements != NULL)
		{
			free(_elements);
		}
		_count = 0;
		_capacity = 0;
	};

	void Add(T element)
	{
		if (_elements == NULL)
		{
			_elements = (T*) malloc(sizeof(T));
			_capacity = 1;
		}
		else if (_count == _capacity)
		{
			_capacity *= 2;
			_elements = (T*) realloc(_elements, _capacity * sizeof(T));
		}

		if (_elements == NULL)
		{
			throw AppException(ErrorMessages::MEMORY_ERROR);
		}

		_elements[_count] = element;
		_count++;
	};

	void TrimExcess()
	{
		if (_count != _capacity)
		{
			_elements = (T*) realloc(_elements, _count * sizeof(T));
			if (_elements == NULL)
			{
				throw AppException(ErrorMessages::MEMORY_ERROR);
			}
			_capacity = _count;
		}
	};

	int GetCount()
	{
		return _count;
	};

	T operator[] (int i)
	{
		return _elements[i];
	};

	T GetElement(int i)
	{
		return _elements[i];
	};

	void Remove(T element)
	{
		for (int i = 0; i < _count; i++)
		{
			if (element == _elements[i])
			{
				for(int j = i; j < _count - 1; j++)
				{
					_elements[j] = _elements[j + 1];
				}
				_count--;

				return;
			}
		}
	}

	T* GetElements() 
	{
		return _elements;
	}

	T GetLast()
	{
		return _elements[_count - 1];
	}

	void AddRange(TList<T>* elements) 
	{
		int elementsCount = elements->GetCount();
		if (_capacity == 0)
		{
			_elements = (T*) malloc(elementsCount*sizeof(T));
			_capacity = elementsCount;
		}
		else if(elementsCount > _capacity - _count)
		{
			_elements = (T*) realloc(_elements, (_count + elementsCount)*sizeof(T));
			if (_elements == NULL)
			{
				throw AppException(ErrorMessages::MEMORY_ERROR);
			}
			_capacity = _count + elementsCount;
		}

		for(int i = 0; i < elementsCount; i++)
		{
			_elements[_count] = elements->GetElement(i);
			_count++;
		}

	}

private:
	T* _elements;
	int _count;
	int _capacity;
};

#endif
