#include "ArchExecutor.h"
#include <limits.h>
#include "LzwEncoder.h"
#include "LzwDecoder.h"

void ArchExecutor::Execute(Options* options)
{
	if (options->Recursive)
	{
		int dirCount = options->Dirs->GetCount();

		for (int i = 0; i < dirCount; i++)
		{
			FillFilesFromDir(options->Files, options->Dirs->GetElement(i));
		}
	}

	if (options->Test)
	{
		CheckFileIntagrity(options);
	}

	if (options->List)
	{
		ListCompressionInfo(options);

		return;
	}

	if (options->Code)
	{
		int filesCount = options->Files->GetCount();
		for(int i = 0; i < filesCount; i++)
		{
			char* path = options->Files->GetElement(i);
			char* compressedPath = new char[PATH_MAX];
			int pathLength = sprintf (compressedPath, "%s.ar", path);
			if (pathLength >= PATH_MAX) 
			{
				printf ("Path length has got too long.\n");
				continue;
			}

			char* fileName = GetName(path);
			if (IsCompressedFile(fileName))
			{
				continue;
			}

			FILE* inputFile = fopen(path, "rb");
			FILE* outputFile = fopen(compressedPath, "wb");
			LzwEncoder encoder(inputFile, outputFile);
			encoder.WriteStartInfo(fileName);
			encoder.Encode();
		}
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
		//TODO: ���� ����� ����� ������ long, �� ����� ������ ��������.
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

void ArchExecutor::FillFilesFromDir(TList<char*>* files, const char* dirName)
{
    DIR* dir = opendir(dirName);

    if (!dir) 
	{
        printf ("Cannot open directory '%s'\n", dirName);
        return;
    }

    while (true) {
        struct dirent * entry;
        char* dName;
		char* path = new char[PATH_MAX];

        entry = readdir (dir);
        if (! entry) 
		{
            break;
        }

		dName = entry->d_name;
		int pathLength = sprintf (path, "%s/%s", dirName, dName);
		if (pathLength >= PATH_MAX) 
		{
			printf ("Path length has got too long.\n");
			continue;
		}

		// ���������, �������� �� �����������
        if (entry->d_type & DT_DIR) 
		{
            // ���������, ��� ��� �� ���� ���������� � �� ������������ ����������

            if (strcmp (dName, "..") != 0 && strcmp (dName, ".") != 0) 
			{
                FillFilesFromDir(files, path);
            }
        }
		else
		{
			files->Add(path);
		}
    }

    if (closedir (dir)) 
	{
        printf ("Could not close '%s'\n", dirName);
    }
}

char* ArchExecutor::GetName(char* path)
{
	char *fileName = NULL;

	if (path == NULL)
	{
		return NULL;
	}

	fileName = strrchr(path, '/');

	return fileName == NULL ? path : fileName + 1;
}

bool ArchExecutor::IsCompressedFile(char* fileName)
{
	char* extention = strrchr(fileName, '.');
	if (extention == NULL)
	{
		return false;
	}

	return strcmp(extention, ".ar") == 0;
}
