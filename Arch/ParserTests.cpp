#include "gtest/gtest.h"
#include "Parser.h"

TEST(ParserTest, ShouldParseOneOptionOneFile)
{
	Parser parser;
	char* argv[3] = {"arch", "-d", "file.txt"};
	Options* options = parser.Parse(3, argv);

	ASSERT_TRUE(options->Decode);
	ASSERT_EQ(1, options->Files->GetCount());
	ASSERT_EQ("file.txt", options->Files->GetElement(0));
}

TEST(ParserTest, ShouldParseSeveralOptionsInOne)
{
	Parser parser;
	char* argv[3] = {"arch", "-cr9", "file.txt"};
	Options* options = parser.Parse(3, argv);

	ASSERT_TRUE(options->Code);
	ASSERT_TRUE(options->Recursive);
	ASSERT_TRUE(options->Best);
	ASSERT_EQ(1, options->Files->GetCount());
	ASSERT_EQ("file.txt", options->Files->GetElement(0));
}

TEST(ParserTest, ShouldParseSeveralOptionsInDiff)
{
	Parser parser;
	char* argv[5] = {"arch", "-c", "-r", "-1", "file.txt"};
	Options* options = parser.Parse(5, argv);

	ASSERT_TRUE(options->Code);
	ASSERT_TRUE(options->Recursive);
	ASSERT_TRUE(options->Fast);
	ASSERT_EQ(1, options->Files->GetCount());
	ASSERT_EQ("file.txt", options->Files->GetElement(0));
}

TEST(ParserTest, ShouldParseSeveralFiles)
{
	Parser parser;
	char* argv[6] = {"arch", "-c", "-r", "file1.txt", "file2", "f3"};
	Options* options = parser.Parse(6, argv);

	ASSERT_TRUE(options->Code);
	ASSERT_TRUE(options->Recursive);
	ASSERT_EQ(3, options->Files->GetCount());
	ASSERT_EQ("file1.txt", options->Files->GetElement(0));
	ASSERT_EQ("file2", options->Files->GetElement(1));
	ASSERT_EQ("f3", options->Files->GetElement(2));
}

TEST(ParserTest, ShouldParseStdin)
{
	Parser parser;
	char* argv[3] = {"arch", "-c", "-"};
	Options* options = parser.Parse(3, argv);

	ASSERT_TRUE(options->Code);
	ASSERT_TRUE(options->Stdin);
	ASSERT_EQ(0, options->Files->GetCount());
}