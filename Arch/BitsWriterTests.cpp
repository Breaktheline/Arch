#include "gtest/gtest.h"
#include "BitsWriter.h"

TEST(BitsWriterTest, ShouldWriteByte)
{
	FILE* outputFile = fopen("Tests/test1", "wb");
	BitsWriter bitsWriter(outputFile);
	bitsWriter.AddBitsToBuffer(153);
	bitsWriter.WriteReminder();
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

TEST(BitsWriterTest, ShouldChangeCodeSize)
{
	FILE* outputFile = fopen("Tests/test3", "wb");
	BitsWriter bitsWriter(outputFile);
	bitsWriter.AddBitsToBuffer(153);
	bitsWriter.AddBitsToBuffer(390);
	bitsWriter.AddBitsToBuffer(522);
	bitsWriter.AddBitsToBuffer(7522);
	bitsWriter.WriteReminder();
}

TEST(BitsWriterTest, ShouldNotWriteEmptyReminder)
{
	FILE* outputFile = fopen("Tests/test", "wb");
	BitsWriter bitsWriter(outputFile);
	bitsWriter.WriteReminder();
}