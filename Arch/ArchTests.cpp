#include "gtest/gtest.h"
#include "LzwEncoder.h"
#include "LzwDecoder.h"

TEST(EncoderTest, ShouldEncodeFileWithoutRepetition)
{
	FILE* inputFile = fopen("Tests/ToEncode/in1", "rb");
	FILE* outputFile = fopen("Tests/ToDecode/out1", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.WriteStartInfo("in1");
	encoder.Encode();
}

TEST(DecoderTest, ShouldDecodeFileWithoutRepetition)
{
	FILE* inputFile = fopen("Tests/ToDecode/out1", "rb");
	FILE* outputFile = fopen("Results/dec1", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}

TEST(EncoderTest, ShouldEncodeFileWithRepetition)
{
	FILE* inputFile = fopen("Tests/ToEncode/in2", "rb");
	FILE* outputFile = fopen("Tests/ToDecode/out2", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.WriteStartInfo("in2");
	encoder.Encode();
}

TEST(DecoderTest, ShouldDecodeFileWithRepetition)
{
	FILE* inputFile = fopen("Tests/ToDecode/out2", "rb");
	FILE* outputFile = fopen("Results/dec2", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}

TEST(EncoderTest, ShouldEncodeFileWithoutPath)
{
	FILE* inputFile = fopen("in2", "rb");
	FILE* outputFile = fopen("out2", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.WriteStartInfo("in2");
	encoder.Encode();
}

TEST(EncoderTest, ShouldEncodeEmptyFiles)
{
	FILE* inputFile = fopen("Tests/ToEncode/in3", "rb");
	FILE* outputFile = fopen("Tests/ToDecode/out3", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.WriteStartInfo("in3");
	encoder.Encode();
}

TEST(DecoderTest, ShouldDecodeEmptyFiles)
{
	FILE* inputFile = fopen("Tests/ToDecode/out3", "rb");
	FILE* outputFile = fopen("Results/dec3", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}

TEST(EncoderTest, ShouldEncodeCaseWhenDecoderDoesntKnowCode)
{
	FILE* inputFile = fopen("Tests/ToEncode/in4", "rb");
	FILE* outputFile = fopen("Tests/ToDecode/out4", "wb");
	LzwEncoder encoder(inputFile, outputFile);
	encoder.WriteStartInfo("Tests/in4");
	encoder.Encode();
}

TEST(DecoderTest, ShouldDecodeCaseWhenDecoderDoesntKnowCode)
{
	FILE* inputFile = fopen("Tests/ToDecode/out4", "rb");
	FILE* outputFile = fopen("Results/dec4", "wb");
	LzwDecoder decoder(inputFile, outputFile);
	decoder.Decode();
}
