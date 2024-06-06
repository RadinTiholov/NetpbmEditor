#pragma once
#include "RasterFile.h"

class PPMFile : RasterFile
{
public:
	RasterFile* clone() const override;
};
