#pragma once
#include "RasterFile.h"

class FileFactory
{
public:
	static RasterFile* createFile(const char* fileName);
};

