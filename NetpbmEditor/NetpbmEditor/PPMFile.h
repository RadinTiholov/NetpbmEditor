#pragma once
#include "RasterFile.h"

class PPMFile : public RasterFile
{
public:
	RasterFile* clone() const override;
	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotate() override;
};
