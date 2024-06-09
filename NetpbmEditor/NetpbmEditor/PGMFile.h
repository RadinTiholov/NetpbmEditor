#pragma once
#include "RasterFile.h"
#include "Vector.hpp"

class PGMFile : public RasterFile
{
private:
	unsigned maxValue = 0;
	Vector<uint16_t> content;
	void setMaxValue(unsigned maxValue);
	void writeMaxValue(std::ofstream& ofs) const;
public:
	PGMFile(unsigned magicNumber, unsigned width, unsigned height, Encoding encoding, const char* fileName, unsigned maxValue, Vector<uint16_t> values);
	RasterFile* clone() const override;
	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotate() override;

	void serialize() const override;
};
