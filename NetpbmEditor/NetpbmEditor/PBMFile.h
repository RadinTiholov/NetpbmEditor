#pragma once
#include "RasterFile.h"
#include "DynamicSet.h"
#include "Constants.h"

class PBMFile : public RasterFile
{
private:
	DynamicSet content;
	void setMagicNumber(unsigned newMagicNumber);
	void setWidth(unsigned newWidth);
	void setHeigth(unsigned newHeight);
public:
	PBMFile(unsigned magicNumber, unsigned width, unsigned height, Encoding encoding, const DynamicSet& set);
	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotate() override;
	RasterFile* clone() const override;
};