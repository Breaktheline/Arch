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
		return;
	}

	if (options->List)
	{
		CheckFileIntagrity(options);
		ListCompressionInfo(options);
		return;
	}

	if (options->Code)
	{
		EncodeFilesToStdout(options);
		return;
	}

	if (options->Decode)
	{
		CheckFileIntagrity(options);
		DecodeFiles(options);
		return;
	}

	EncodeFiles(options);
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

bool ArchExecutor::CheckCrc(FILE* file)
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
	if (file < 0)
	{
		return 0;
	}
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
		char* path = options->Files->GetElement(i);
		FILE* file = fopen(path, "rb");
		if (IsCompressedFile(file) && !CheckCrc(file))
		{
			printf("arch: %s: invalid compressed data--crc error\n", GetName(path));
		}
		fclose(file);
	}
}

void ArchExecutor::ListCompressionInfo(Options* options)
{
	int filesCount = options->Files->GetCount();
	printf("compressed\t uncompressed: \t ratio\t  uncompressed_name\n");
	for(int i = 0; i < filesCount; i++)
	{
		FILE* file = fopen(options->Files->GetElement(i), "rb");
		char* filename = ReadFileName(file);
		unsigned long fileSize = ReadUncompressedSize(file);
		unsigned long compressedFileSize = GetLastFilePosition(file);
		printf("%lu\t\t %lu\t\t %f\t\t", compressedFileSize, fileSize, (double)fileSize/compressedFileSize);
		int j = 0;
		while (filename[j]!= '\0')
		{
			printf("%c", filename[j]);
			j++;
		}

		printf("\n");
		fclose(file);
	}
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
	
	filename[i] = '\0';
	rewind(file);
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

		// ѕровер€ем, €вл€етс€ ли директорией
        if (entry->d_type & DT_DIR) 
		{
            // ѕровер€ем, что это не сама директори€ и не родительска€ директори€

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

bool ArchExecutor::IsCompressedFile(FILE* file)
{
	byte indexes[2];
	fread(&indexes, 2, 1, file);
	rewind(file);

	return indexes[0] == ID1 && indexes[1] == ID2;
}

void ArchExecutor::EncodeFiles(Options* options)
{
	int filesCount = options->Files->GetCount();
	if (options->Stdin || filesCount == 0)
	{
		LzwEncoder encoder(stdin, stdout);
		encoder.Encode("");
		return;
	}

	for(int i = 0; i < filesCount; i++)
	{
		char* path = options->Files->GetElement(i);

		FILE* inputFile = fopen(path, "rb");
		if (IsCompressedFile(inputFile))
		{
			fclose(inputFile);
			continue;
		}

		char* compressedPath = new char[PATH_MAX];
		int pathLength = sprintf (compressedPath, "%s.ar", path);
		if (pathLength >= PATH_MAX) 
		{
			printf ("Path length has got too long.\n");
			continue;
		}

		FILE* outputFile = fopen(compressedPath, "wb");

		LzwEncoder encoder(inputFile, outputFile);
		encoder.Encode(GetName(path));
		fclose(inputFile);
		remove(path);
	}
}

void ArchExecutor::EncodeFilesToStdout(Options* options)
{
	int filesCount = options->Files->GetCount();
	if (options->Stdin || filesCount == 0)
	{
		LzwEncoder encoder(stdin, stdout);
		encoder.Encode("");
		return;
	}
	
	for(int i = 0; i < filesCount; i++)
	{
		char* path = options->Files->GetElement(i);

		FILE* inputFile = fopen(path, "rb");
		if (IsCompressedFile(inputFile))
		{
			fclose(inputFile);
			continue;
		}
		LzwEncoder encoder(inputFile, stdout);
		encoder.Encode(GetName(path));
		fclose(inputFile);
	}
}

void ArchExecutor::DecodeFiles(Options* options)
{
	int filesCount = options->Files->GetCount();
	for(int i = 0; i < filesCount; i++)
	{
		char* path = options->Files->GetElement(i);
		FILE* inputFile = fopen(path, "rb");
		char* fileName = ReadFileName(inputFile);
		char filePath[PATH_MAX];
		strcpy(filePath, path);
		char* inputFileName = GetName(path);
		filePath[strlen(path) - strlen(inputFileName) - 1] = '\0';
		char decompressedPath[PATH_MAX];
		int pathLength = sprintf (decompressedPath, "%s/%s", filePath, fileName);
		if (pathLength >= PATH_MAX) 
		{
			printf ("Path length has got too long.\n");
			continue;
		}
		
		FILE* outputFile = fopen(decompressedPath, "wb");
		if (!IsCompressedFile(inputFile))
		{
			fclose(inputFile);
			continue;
		}

		LzwDecoder decoder(inputFile, outputFile);
		decoder.Decode();
		fclose(inputFile);
		remove(path);
	}
}
