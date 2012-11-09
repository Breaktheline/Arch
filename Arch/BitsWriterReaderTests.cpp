#include "gtest/gtest.h"
#include "BitsWriter.h"
#include "BitsReader.h"

TEST(BitsWriterTest, ShouldWriteByte)
{
	FILE* outputFile = fopen("Tests/test1", "wb");
	BitsWriter bitsWriter(outputFile);
	bitsWriter.AddBitsToBuffer(153);
	bitsWriter.WriteReminder();
}

TEST(BitsReaderTest, ShouldReadCode)
{
	FILE* inputFile = fopen("Tests/test1", "rb");
	BitsReader bitsReader(inputFile);
	int code = bitsReader.ReadNextBits();
	ASSERT_EQ(153, code);
}

TEST(BitsWriterTest, ShouldWriteSeveralBytes)
{
	FILE* outputFile = fopen("Tests/test2", "wb");
	BitsWriter bitsWriter(outputFile);
	bitsWriter.AddBitsToBuffer(153);
	bitsWriter.AddBitsToBuffer(90);
	bitsWriter.AddBitsToBuffer(222);
	bitsWriter.WriteReminder();
}

TEST(BitsReaderTest, ShouldReadSeveralCodes)
{
	FILE* inputFile = fopen("Tests/test2", "rb");
	BitsReader bitsReader(inputFile);
	int code1 = bitsReader.ReadNextBits();
	int code2 = bitsReader.ReadNextBits();
	int code3 = bitsReader.ReadNextBits();

	ASSERT_EQ(153, code1);
	ASSERT_EQ(90, code2);
	ASSERT_EQ(222, code3);
}

TEST(BitsWriterTest, ShouldChangeCodeSize)
{
	FILE* outputFile = fopen("Tests/test3", "wb");
	BitsWriter bitsWriter(outputFile);
	bitsWriter.AddBitsToBuffer(153);
	bitsWriter.AddBitsToBuffer(390);
	bitsWriter.AddBitsToBuffer(522);
	bitsWriter.AddBitsToBuffer(1222);
	bitsWriter.WriteReminder();
}

TEST(BitsReaderTest, ShouldReadSeveralCodesWithDiffCodeSize)
{
	FILE* inputFile = fopen("Tests/test3", "rb");
	BitsReader bitsReader(inputFile);
	int code1 = bitsReader.ReadNextBits();
	int code2 = bitsReader.ReadNextBits();
	int code3 = bitsReader.ReadNextBits();
	int code4 = bitsReader.ReadNextBits();

	ASSERT_EQ(153, code1);
	ASSERT_EQ(390, code2);
	ASSERT_EQ(522, code3);
	ASSERT_EQ(1222, code4);
}

TEST(BitsWriterTest, ShouldNotWriteEmptyReminder)
{
	FILE* outputFile = fopen("Tests/test", "wb");
	BitsWriter bitsWriter(outputFile);
	bitsWriter.WriteReminder();
}

TEST(BitsWriterTest, ShouldReadEmptyFile)
{
	FILE* inputFile = fopen("Tests/test", "rb");
	BitsReader bitsReader(inputFile);
	int code = bitsReader.ReadNextBits();

	ASSERT_EQ(NIL, code);
}