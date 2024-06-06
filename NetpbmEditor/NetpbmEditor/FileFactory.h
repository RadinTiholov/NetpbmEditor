#pragma once
#include "RasterFile.h"
#include "Constants.h"
#include <fstream>

class FileFactory
{
public:
	static RasterFile* createFile(const char* fileName);
};

