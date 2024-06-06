#pragma once
#include "RasterFile.h"

class PBMFile : public RasterFile
{
public:
	PBMFile(unsigned magicNumber, unsigned width, unsigned height);
	RasterFile* clone() const override;
	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotate() override;
};