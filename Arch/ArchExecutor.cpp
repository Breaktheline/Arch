#include "ArchExecutor.h"

void ArchExecutor::Execute(Options* options)
{
	if (options->Recursive)
	{
		int dirCount = options->Files->GetCount();

		for (int i = 0; i < dirCount; i++)
		{
			DIR *dir;
			struct dirent *ent;
			dir = opendir (options->Files->GetElement(i));
			
			if (dir != NULL) 
			{
				/* print all the files and directories within directory */
				while ((ent = readdir (dir)) != NULL) 
				{
					options->Files->Add(ent->d_name);
				}
				closedir (dir);
			} 
			else 
			{
				/* could not open directory */
				perror ("");
			}
		}
	}

	if (options->Test)
	{
		CheckFileIntagrity(options);

		return;
	}

	if (options->List)
	{
		ListCompressionInfo(options);

		return;
	}
}

unsigned long ArchExecutor::ReadCrcFromFile(FILE* file)
{
	fseek(file, -CRC_SIZE_BYTES-FILE_SIZE_BYTES, SEEK_END);
	unsigned long crc;
	fread(&crc, CRC_SIZE_BYTES, 1, file);
	rewind(file);
	return crc;
}

unsigned long ArchExecutor::MakeCrc(FILE* file)
{
	int nextByte;
	unsigned long crc = 0L;
	byte buffer[CRC_BUFFER_SIZE];
	int bufferLength;

	long lastPosition = GetLastFilePosition(file);

	while((bufferLength = ReadToBuffer(buffer, file)) > 0)
	{
		//TODO: если длина файла больше long, то нужна друга€ проверка.
		if (ftell(file) == lastPosition)
		{
			bufferLength -= CRC_SIZE_BYTES + FILE_SIZE_BYTES;
		}

		crc = _crcMaker.UpdateCrc(crc, buffer, bufferLength);
	}

	rewind(file);

	return crc;
}

bool ArchExecutor::CheckCrc( FILE* file )
{
	return ReadCrcFromFile(file) == MakeCrc(file);
}

unsigned int ArchExecutor::ReadToBuffer( byte* buffer, FILE* file )
{
	return fread(buffer, sizeof(byte), CRC_BUFFER_SIZE, file);
}

unsigned long ArchExecutor::ReadUncompressedSize(FILE* file)
{
	fseek(file, -FILE_SIZE_BYTES, SEEK_END);
	unsigned long size;
	fread(&size, FILE_SIZE_BYTES, 1, file);
	rewind(file);

	return size;
}

unsigned long ArchExecutor::GetLastFilePosition(FILE* file)
{
	fseek(file, 0, SEEK_END);
	long lastFilePosition = ftell(file);
	rewind(file);
	return lastFilePosition;
}

void ArchExecutor::CheckFileIntagrity(Options* options)
{
	int filesCount = options->Files->GetCount();
	for(int i = 0; i < filesCount; i++)
	{
		FILE* file = fopen(options->Files->GetElement(i), "rb");
		if (!CheckCrc(file))
		{
			printf("invalid compressed data--crc error\n");
		}
		fclose(file);
	}
}

void ArchExecutor::ListCompressionInfo(Options* options)
{
	int filesCount = options->Files->GetCount();
	for(int i = 0; i < filesCount; i++)
	{
		FILE* file = fopen(options->Files->GetElement(i), "rb");
		OutputCompressInfo(file);
		fclose(file);
	}
}

void ArchExecutor::OutputCompressInfo(FILE* file)
{
	char* filename = ReadFileName(file);
	unsigned long fileSize = ReadUncompressedSize(file);
	unsigned long conpressedFileSize = GetLastFilePosition(file);
	printf("compressed size: %lu\t uncompressed size: %lu\n", conpressedFileSize, fileSize);
	printf("ratio: %f%%\t uncompressed_name: ", conpressedFileSize/fileSize);
	int i = 0;
	while (filename[i]!= '\0')
	{
		printf("%c", filename[i]);
		i++;
	}

	printf("\n");
}

char* ArchExecutor::ReadFileName(FILE* file)
{
	fseek(file, 2, SEEK_SET);
	char b;
	int i = 0;
	char* filename = new char[FILENAME_MAX];
	while ((b = fgetc(file)) != '\0')
	{
		filename[i] = b;
		i++;
	}

	//fread(filename, sizeof(char), 4, file);

	filename[i] = '\0';

	return filename;
}
