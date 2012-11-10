#include "gtest/gtest.h"
#include "LzwEncoder.h"
#include "LzwDecoder.h"

TEST(EncoderTest, ShouldEncodeFileWithoutRepetition)
{
	FILE* inputFile = fopen("Tests/in1", "rb");
	FILE* outputFile = fopen("Tests/out1", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.Encode();
}

TEST(DecoderTest, ShouldDecodeFileWithoutRepetition)
{
	FILE* inputFile = fopen("Tests/out1", "rb");
	FILE* outputFile = fopen("Tests/dec1", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}

TEST(EncoderTest, ShouldEncodeFileWithRepetition)
{
	FILE* inputFile = fopen("Tests/in2", "rb");
	FILE* outputFile = fopen("Tests/out2", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.Encode();
}

TEST(DecoderTest, ShouldDecodeFileWithRepetition)
{
	FILE* inputFile = fopen("Tests/out2", "rb");
	FILE* outputFile = fopen("Tests/dec2", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}

TEST(EncoderTest, ShouldEncodeEmptyFiles)
{
	FILE* inputFile = fopen("Tests/in3", "rb");
	FILE* outputFile = fopen("Tests/out3", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.Encode();
}

TEST(DecoderTest, ShouldDecodeEmptyFiles)
{
	FILE* inputFile = fopen("Tests/out3", "rb");
	FILE* outputFile = fopen("Tests/dec3", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}

TEST(EncoderTest, ShouldEncodeCaseWhenDecoderDoesntKnowCode)
{
	FILE* inputFile = fopen("Tests/in4", "rb");
	FILE* outputFile = fopen("Tests/out4", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.Encode();
}

TEST(DecoderTest, ShouldEncodeCaseWhenDecoderDoesntKnowCode)
{
	FILE* inputFile = fopen("Tests/out4", "rb");
	FILE* outputFile = fopen("Tests/dec4", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}
