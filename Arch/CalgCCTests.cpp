//#include "gtest/gtest.h"
//#include "LzwEncoder.h"
//#include "LzwDecoder.h"
//
//TEST(CalgEncodeTest, ShouldEncodeBib)
//{
//	FILE* inputFile = fopen("CalgCC/bib", "rb");
//	FILE* outputFile = fopen("CalgCC/bibOut", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodeBib)
//{
//	FILE* inputFile = fopen("CalgCC/bibOut", "rb");
//	FILE* outputFile = fopen("CalgCC/bibDec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodeBook1)
//{
//	FILE* inputFile = fopen("CalgCC/book1", "rb");
//	FILE* outputFile = fopen("CalgCC/book1Out", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodeBook1)
//{
//	FILE* inputFile = fopen("CalgCC/book1Out", "rb");
//	FILE* outputFile = fopen("CalgCC/book1Dec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodeBook2)
//{
//	FILE* inputFile = fopen("CalgCC/book2", "rb");
//	FILE* outputFile = fopen("CalgCC/book2Out", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodeBook2)
//{
//	FILE* inputFile = fopen("CalgCC/book2Out", "rb");
//	FILE* outputFile = fopen("CalgCC/book2Dec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodeGeo)
//{
//	FILE* inputFile = fopen("CalgCC/geo", "rb");
//	FILE* outputFile = fopen("CalgCC/geoOut", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodeGeo)
//{
//	FILE* inputFile = fopen("CalgCC/geoOut", "rb");
//	FILE* outputFile = fopen("CalgCC/geoDec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodeNews)
//{
//	FILE* inputFile = fopen("CalgCC/news", "rb");
//	FILE* outputFile = fopen("CalgCC/newsOut", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodeNews)
//{
//	FILE* inputFile = fopen("CalgCC/newsOut", "rb");
//	FILE* outputFile = fopen("CalgCC/newsDec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodeObj1)
//{
//	FILE* inputFile = fopen("CalgCC/obj1", "rb");
//	FILE* outputFile = fopen("CalgCC/obj1Out", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodeObj1)
//{
//	FILE* inputFile = fopen("CalgCC/obj1Out", "rb");
//	FILE* outputFile = fopen("CalgCC/obj1Dec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodeObj2)
//{
//	FILE* inputFile = fopen("CalgCC/obj2", "rb");
//	FILE* outputFile = fopen("CalgCC/obj2Out", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodeObj2)
//{
//	FILE* inputFile = fopen("CalgCC/obj2Out", "rb");
//	FILE* outputFile = fopen("CalgCC/obj2Dec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodePaper1)
//{
//	FILE* inputFile = fopen("CalgCC/paper1", "rb");
//	FILE* outputFile = fopen("CalgCC/paper1Out", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodePaper1)
//{
//	FILE* inputFile = fopen("CalgCC/paper1Out", "rb");
//	FILE* outputFile = fopen("CalgCC/paper1Dec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodePaper2)
//{
//	FILE* inputFile = fopen("CalgCC/paper2", "rb");
//	FILE* outputFile = fopen("CalgCC/paper2Out", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodePaper2)
//{
//	FILE* inputFile = fopen("CalgCC/paper2Out", "rb");
//	FILE* outputFile = fopen("CalgCC/paper2Dec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodePic)
//{
//	FILE* inputFile = fopen("CalgCC/pic", "rb");
//	FILE* outputFile = fopen("CalgCC/picOut", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodePic)
//{
//	FILE* inputFile = fopen("CalgCC/picOut", "rb");
//	FILE* outputFile = fopen("CalgCC/picDec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodeProgc)
//{
//	FILE* inputFile = fopen("CalgCC/progc", "rb");
//	FILE* outputFile = fopen("CalgCC/progcOut", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodeProgc)
//{
//	FILE* inputFile = fopen("CalgCC/progcOut", "rb");
//	FILE* outputFile = fopen("CalgCC/progcDec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodeProgl)
//{
//	FILE* inputFile = fopen("CalgCC/progl", "rb");
//	FILE* outputFile = fopen("CalgCC/proglOut", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodeProgl)
//{
//	FILE* inputFile = fopen("CalgCC/proglOut", "rb");
//	FILE* outputFile = fopen("CalgCC/proglDec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodeProgp)
//{
//	FILE* inputFile = fopen("CalgCC/progp", "rb");
//	FILE* outputFile = fopen("CalgCC/progpOut", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodeProgp)
//{
//	FILE* inputFile = fopen("CalgCC/progpOut", "rb");
//	FILE* outputFile = fopen("CalgCC/progpDec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}
//
//TEST(CalgEncodeTest, ShouldEncodeTrans)
//{
//	FILE* inputFile = fopen("CalgCC/trans", "rb");
//	FILE* outputFile = fopen("CalgCC/transOut", "wb");
//	LzwEncoder encoder(inputFile, outputFile);
//	encoder.Encode();
//}
//
//TEST(CalgDecodeTest, ShouldDecodeTrans)
//{
//	FILE* inputFile = fopen("CalgCC/transOut", "rb");
//	FILE* outputFile = fopen("CalgCC/transDec", "wb");
//	LzwDecoder decoder(inputFile, outputFile);
//	decoder.Decode();
//}