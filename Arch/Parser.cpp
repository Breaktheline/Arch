#include "Parser.h"

Options* Parser::Parse(int argc, char** argv)
{
	if (argc == 1)
	{
		printf("Wrong command");
		return NULL;
	}

	char* arg = argv[1];
	Options* options = new Options();

	int optionsCount = 0;
	for(int i = 1; i < argc; i++)
	{
		char* argPointer = argv[i];
		//Если это не аргумент.
		if (*argPointer != HYPHEN)
		{
			break;
		}

		optionsCount++;

		//Если пустой дефис.
		if (*++argPointer == NULL)
		{
			options->Stdin = true;
		}

		while(*++argPointer != NULL)
		{
			SetOption(*argPointer, *options);
		}
	}

	//количество указанных файлов.
	for (int i = optionsCount; i < argc; i++)
	{
		options->Files->Add(argv[i]);
	}

	return options;
}

void Parser::SetOption(char arg, Options &options)
{
	switch(arg)
	{
	case 'c':
		{
			options.Code = true;
			break;
		}
	case 'd':
		{
			options.Decode = true;
			break;
		}
	case 't':
		{
			options.Test = true;
			break;
		}
	case 'l':
		{
			options.List = true;
			break;
		}
	case 'r':
		{
			options.Recursive = true;
			break;
		}
	case '1':
		{
			options.Fast = true;
			break;
		}
	case '9':
		{
			options.Best = true;
			break;
		}
	}
}