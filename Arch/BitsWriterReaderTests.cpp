#include "gtest/gtest.h"
#include "BitsWriter.h"
#include "BitsReader.h"

TEST(BitsWriterTest, ShouldWriteByte)
{
	FILE* outputFile = fopen("Results/test1", "wb");
	BitsWriter bitsWriter(outputFile);
	bitsWriter.AddBitsToBuffer(153);
	bitsWriter.WriteEndOfFile(1);
}

TEST(BitsReaderTest, ShouldReadCode)
{
	FILE* inputFile = fopen("Results/test1", "rb");
	BitsReader bitsReader(inputFile);
	int code = bitsReader.ReadNextBits();

	ASSERT_EQ(153, code);
}

TEST(BitsWriterTest, ShouldWriteSeveralBytes)
{
	FILE* outputFile = fopen("Results/test2", "wb");
	BitsWriter bitsWriter(outputFile);
	bitsWriter.AddBitsToBuffer(153);
	bitsWriter.AddBitsToBuffer(90);
	bitsWriter.AddBitsToBuffer(222);
	bitsWriter.WriteEndOfFile(3);
}

TEST(BitsReaderTest, ShouldReadSeveralCodes)
{
	FILE* inputFile = fopen("Results/test2", "rb");
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
	FILE* outputFile = fopen("Results/test3", "wb");
	BitsWriter bitsWriter(outputFile);
	bitsWriter.AddBitsToBuffer(153);
	bitsWriter.AddBitsToBuffer(390);
	bitsWriter.AddBitsToBuffer(522);
	bitsWriter.AddBitsToBuffer(1222);
	bitsWriter.WriteEndOfFile(8);
}

TEST(BitsReaderTest, ShouldReadSeveralCodesWithDiffCodeSize)
{
	FILE* inputFile = fopen("Results/test3", "rb");
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
	FILE* outputFile = fopen("Results/test", "wb");
	BitsWriter bitsWriter(outputFile);
	bitsWriter.WriteEndOfFile(2);
}

TEST(BitsWriterTest, ShouldReadEmptyFile)
{
	FILE* inputFile = fopen("Results/test", "rb");
	BitsReader bitsReader(inputFile);
	int code = bitsReader.ReadNextBits();

	ASSERT_EQ(NIL, code);
}