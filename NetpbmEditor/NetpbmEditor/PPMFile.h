#pragma once
#include "RasterFile.h"
#include "RGBData.h"
#include "Vector.hpp"

class PPMFile : public RasterFile
{
public:
	PPMFile(unsigned magicNumber, unsigned width, unsigned height, Encoding encoding, const char* fileName, unsigned maxValue, Vector<RGBData> values);
	RasterFile* clone() const override;
	void grayscale() override;
	void monochrome() override;
	void negative() override;

	void serialize() const override;
private:
	unsigned maxValue = 0;
	Vector<RGBData> content;
	void setMaxValue(unsigned maxValue);
	void writeMaxValue(std::ofstream& ofs) const;
	void serializeContentToBinary(std::ofstream& ofs) const;

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
