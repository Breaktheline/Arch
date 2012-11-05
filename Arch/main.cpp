
#include "gtest/gtest.h"

void Execute(FILE* inputFile = stdin)
{

}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();

	//Execute();
}

