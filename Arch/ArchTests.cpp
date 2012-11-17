#include "gtest/gtest.h"
#include "LzwEncoder.h"
#include "LzwDecoder.h"

TEST(EncoderTest, ShouldEncodeFileWithoutRepetition)
{
	FILE* inputFile = fopen("Tests/in1", "rb");
	FILE* outputFile = fopen("Results/out1", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.Encode();
}

TEST(DecoderTest, ShouldDecodeFileWithoutRepetition)
{
	FILE* inputFile = fopen("Results/out1", "rb");
	FILE* outputFile = fopen("Results/dec1", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}

TEST(EncoderTest, ShouldEncodeFileWithRepetition)
{
	FILE* inputFile = fopen("Tests/in2", "rb");
	FILE* outputFile = fopen("Results/out2", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.Encode();
}

TEST(DecoderTest, ShouldDecodeFileWithRepetition)
{
	FILE* inputFile = fopen("Results/out2", "rb");
	FILE* outputFile = fopen("Results/dec2", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}

TEST(EncoderTest, ShouldEncodeEmptyFiles)
{
	FILE* inputFile = fopen("Tests/in3", "rb");
	FILE* outputFile = fopen("Results/out3", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.Encode();
}

TEST(DecoderTest, ShouldDecodeEmptyFiles)
{
	FILE* inputFile = fopen("Results/out3", "rb");
	FILE* outputFile = fopen("Results/dec3", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}

TEST(EncoderTest, ShouldEncodeCaseWhenDecoderDoesntKnowCode)
{
	FILE* inputFile = fopen("Tests/in4", "rb");
	FILE* outputFile = fopen("Results/out4", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.Encode();
}

TEST(DecoderTest, ShouldDecodeCaseWhenDecoderDoesntKnowCode)
{
	FILE* inputFile = fopen("Results/out4", "rb");
	FILE* outputFile = fopen("Results/dec4", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}
