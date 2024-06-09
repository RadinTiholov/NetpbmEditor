#include "RasterFile.h"

void RasterFile::writeMagicNumber(std::ofstream& ofs) const 
{
	ofs << 'P' << this->magicNumber << '\n';
}
void RasterFile::writeWidthAndHeight(std::ofstream& ofs) const
{
	ofs << this->width << ' ' << this->height << ' ';
}