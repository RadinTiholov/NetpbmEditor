#pragma once
#include "RasterFile.h"
#include "DynamicSet.h"
#include "Constants.h"
#include "PBMFile.h"
#include "PPMFile.h"
#include "PGMFile.h"
#include <fstream>
#include "Vector.hpp"

class FileFactory
{
public:
	static RasterFile* createFile(const char* fileName);
};

