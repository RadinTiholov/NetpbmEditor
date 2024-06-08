#include "PBMFile.h"

PBMFile::PBMFile(unsigned magicNumber, unsigned width, unsigned height, Encoding encoding, const DynamicSet& set)
{
	setMagicNumber(magicNumber);
	setWidth(width);
	setHeigth(height);
	this->encoding = encoding;
	this->content = set;
}

void PBMFile::setMagicNumber(unsigned newMagicNumber) 
{
	if (newMagicNumber < 0 || newMagicNumber > 6)
	{
		throw std::invalid_argument(Constants::INVALID_MAGIC_NUMBER);
	}
	this->magicNumber = newMagicNumber;
}

void PBMFile::setWidth(unsigned newWidth) 
{
	if (newWidth < 0)
	{
		throw std::invalid_argument(Constants::INVALID_WIDTH);
	}
	this->width = newWidth;
}

void PBMFile::setHeigth(unsigned newHeight) 
{
	if (newHeight < 0)
	{
		throw std::invalid_argument(Constants::INVALID_HEIGHT);
	}
	this->height = newHeight;
}

RasterFile* PBMFile::clone() const
{
	return new PBMFile(*this);
}

void PBMFile::grayscale()
{

}

void PBMFile::monochrome()
{

};

void PBMFile::negative()
{

};

void PBMFile::rotate()
{

}