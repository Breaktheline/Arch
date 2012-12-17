#include "gtest/gtest.h"
#include "ArchExecutor.h"

TEST(ExecutorTest, ShouldTestGoodFile)
{
	Options* options = new Options();
	options->Test = true;
	options->Files->Add("Tests/out2.ar");

	ArchExecutor executor;
	executor.Execute(options);
}

TEST(ExecutorTest, ShouldTestBadFile)
{
	Options* options = new Options();
	options->Test = true;
	options->Files->Add("Tests/out2_bad.ar");

	ArchExecutor executor;
	executor.Execute(options);
}

TEST(ExecutorTest, ShouldListOneCompressedFile)
{
	Options* options = new Options();
	options->List = true;
	options->Files->Add("Results/out2");

	ArchExecutor executor;
	executor.Execute(options);
}

TEST(ExecutorTest, ShouldListOneCompressedFileWithoutPath)
{
	Options* options = new Options();
	options->List = true;
	options->Files->Add("out2");

	ArchExecutor executor;
	executor.Execute(options);
}

TEST(ExecutorTest, ShouldListSeveralFiles)
{
	Options* options = new Options();
	options->List = true;
	options->Files->Add("Tests/out2.ar");
	options->Files->Add("Tests/out4.ar");

	ArchExecutor executor;
	executor.Execute(options);
}

TEST(ExecutorTest, ShouldRecursiveCompressDir)
{
	Options* options = new Options();
	options->Recursive = true;
	options->Code = true;
	options->Dirs->Add("Tests");

	ArchExecutor executor;
	executor.Execute(options);
}