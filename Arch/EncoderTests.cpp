#include "gtest/gtest.h"
#include "LzwEncoder.h"

TEST(EncoderTest, ShouldEncodeFileWithoutRepetition)
{
	FILE* inputFile = fopen("Tests/in1", "rb");
	FILE* outputFile = fopen("Tests/out1", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.Encode();
}

TEST(EncoderTest, ShouldEncodeFileWithRepetition)
{
	FILE* inputFile = fopen("Tests/in2", "rb");
	FILE* outputFile = fopen("Tests/out2", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.Encode();
}

TEST(EncoderTest, ShouldEncodeDifFiles)
{
	FILE* inputFile = fopen("Tests/in3", "rb");
	FILE* outputFile = fopen("Tests/out3", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.Encode();
}