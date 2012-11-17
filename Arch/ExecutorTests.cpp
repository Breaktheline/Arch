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