#include "RasterFile.h"

void RasterFile::writeMagicNumber(std::ofstream& ofs) const 
{
	ofs << 'P' << this->magicNumber << '\n';
}

void RasterFile::writeWidthAndHeight(std::ofstream& ofs) const
{
	ofs << this->width << ' ' << this->height << ' ';
}

const char* RasterFile::getFileName() const 
{
	return this->fileName.c_str();
}

void RasterFile::setFileName(const char* fileName)
{
	this->fileName = fileName;
}

unsigned RasterFile::getWidth() const 
{
	return this->width;
}

unsigned RasterFile::getHeight() const 
{
	return this->height;
}

void RasterFile::rotate(Direction direction) 
{
	if (direction == Direction::Left)
	{
		this->rotateLeft();
	}
	else if (direction == Direction::Right)
	{
		this->rotateRight();
	}
	unsigned temp = this->height;
	this->height = this->width;
	this->width = temp;
	std::cout << "Rotated successfully" << std::endl;
}

RasterFile* RasterFile::collageWith(const Direction& direction, const RasterFile* other, const char* fileName) const
{
	if (direction == Direction::Horizontal)
	{
		return this->horizontalCollage(other, fileName);
	}
	else if (direction == Direction::Vertical)
	{

		return this->verticalCollage(other, fileName);
	}
}

void RasterFile::setMagicNumber(unsigned newMagicNumber)
{
	if (newMagicNumber < 0 || newMagicNumber > 6)
	{
		throw std::invalid_argument(Constants::INVALID_MAGIC_NUMBER);
	}
	this->magicNumber = newMagicNumber;
}

void RasterFile::setWidth(unsigned newWidth)
{
	if (newWidth < 0)
	{
		throw std::invalid_argument(Constants::INVALID_WIDTH);
	}
	this->width = newWidth;
}

void RasterFile::setHeigth(unsigned newHeight)
{
	if (newHeight < 0)
	{
		throw std::invalid_argument(Constants::INVALID_HEIGHT);
	}
	this->height = newHeight;
}