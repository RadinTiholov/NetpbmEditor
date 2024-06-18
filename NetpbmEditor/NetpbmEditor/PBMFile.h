#pragma once
#include "RasterFile.h"
#include "DynamicSet.h"

class PBMFile : public RasterFile
{
public:
	PBMFile(unsigned magicNumber, unsigned width, unsigned height, Encoding encoding, const char* fileName, const DynamicSet& set);
	void grayscale() override;
	void monochrome() override;
	void negative() override;

	void serialize() const override;
	RasterFile* clone() const override;
private:
	DynamicSet content;
	void serializeContentToBinary(std::ofstream& ofs) const;
	void adjustByteWithExcessBits(int& startBit, uint8_t*& bytes, int excessBits, int currentByteIndex) const;
	void adjustByteWithoutExcessBits(int& startBit, uint8_t*& bytes, int currentByteIndex) const;

	void rotateRight() override;
	void rotateLeft() override;

	RasterFile* horizontalCollage(const RasterFile* other, const char* fileName) const override;
	RasterFile* verticalCollage(const RasterFile* other, const char* fileName) const override;

	RasterFile* horizontalCollageWithPBM(const PBMFile* other, const char* fileName) const override;
	RasterFile* horizontalCollageWithPGM(const PGMFile* other, const char* fileName) const override;
	RasterFile* horizontalCollageWithPPM(const PPMFile* other, const char* fileName) const override;
	RasterFile* verticalCollageWithPBM(const PBMFile* other, const char* fileName) const override;
	RasterFile* verticalCollageWithPGM(const PGMFile* other, const char* fileName) const override;
	RasterFile* verticalCollageWithPPM(const PPMFile* other, const char* fileName) const override;
};