#ifndef H_COMMON
#define H_COMMON

typedef unsigned char byte;
#define MIN_CODE_LEN 9
#define MAX_CODE_LEN 15
#define NIL -1
#define MAX_FILE_SIZE 4294967295
#define CRC_SIZE_BYTES 4
#define FILE_SIZE_BYTES 4
#define CRC_BUFFER_SIZE 1024
#define ID1 31
#define ID2 139

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "dirent.h"
#include "TList.h"

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
		Message = message;
	}

	const char* Message;
};

class FileException
{
public:
	FileException(const char* message, const char* fileName)
	{
		Message = message;
		FileName = fileName;
	}

	const char* Message;
	const char* FileName;
};

#endif
