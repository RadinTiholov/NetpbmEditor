#pragma once
#include "RasterFile.h"

class PGMFile : RasterFile
{
public:
	RasterFile* clone() const override;
};
