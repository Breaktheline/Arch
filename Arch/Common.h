#ifndef H_COMMON
#define H_COMMON

typedef unsigned char byte;
#define MIN_CODE_LEN 8
#define MAX_CODE_LEN 15
#define NIL -1

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct ErrorMessages
{
	static const char* MEMORY_ERROR;
	static const char* FILE_OPEN_ERROR;
	static const char* WRONG_INPUT_ERROR;
};

class AppException 
{
public:
	AppException(const char* message)
	{
		_message = message;
	}

	const char* GetMessage() 
	{ 
		return _message;
	};
private:
	const char* _message;
};


#endif


