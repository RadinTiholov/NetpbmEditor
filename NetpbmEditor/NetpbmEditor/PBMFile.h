#pragma once
#include "RasterFile.h"

class PBMFile : RasterFile
{
public:
	RasterFile* clone() const override;
};