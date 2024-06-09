#pragma once
#include "RasterFile.h"
#include "DynamicSet.h"
#include "Constants.h"

class PBMFile : public RasterFile
{
public:
	PBMFile(unsigned magicNumber, unsigned width, unsigned height, Encoding encoding, const char* fileName, const DynamicSet& set);
	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotate() override;

	void serialize() const override;
	RasterFile* clone() const override;
private:
	DynamicSet content;
	void setMagicNumber(unsigned newMagicNumber);
	void setWidth(unsigned newWidth);
	void setHeigth(unsigned newHeight);
	void serializeContentToBinary(std::ofstream& ofs) const;
	void adjustByteWithExcessBits(int& startBit, uint8_t*& bytes, int excessBits, int currentByteIndex) const;
	void adjustByteWithoutExcessBits(int& startBit, uint8_t*& bytes, int currentByteIndex) const;
};