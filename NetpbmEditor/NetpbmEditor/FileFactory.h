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
private:
	static PBMFile* createPBMASCIIFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName);
	static PBMFile* createPBMBinaryFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName);
	static PGMFile* createPGMASCIIFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName);
	static PGMFile* createPGMBinaryFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName);
	static PPMFile* createPPMASCIIFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName);
	static PPMFile* createPPMBinaryFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName);
};

