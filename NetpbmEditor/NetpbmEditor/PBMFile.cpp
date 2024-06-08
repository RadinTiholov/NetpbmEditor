#include "PBMFile.h"

PBMFile::PBMFile(unsigned magicNumber, unsigned width, unsigned height, Encoding encoding, const char* fileName, const DynamicSet& set)
{
	setMagicNumber(magicNumber);
	setWidth(width);
	setHeigth(height);
	this->fileName = MyString(fileName);
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

void PBMFile::serialize() const
{
	std::ofstream ofs(this->fileName.c_str());
	if (!ofs.is_open())
	{
		throw std::runtime_error(Constants::COULD_NOT_OPEN_FILE_ERROR_MESSAGE);
	}
	this->writeMagicNumber(ofs);
	this->writeWidthAndHeight(ofs);
	if (this->encoding == Encoding::ASCII)
	{
		this->content.serializeToAscii(ofs);
	}
	else if(this->encoding == Encoding::Binary)
	{
		ofs.close();
		ofs.open(this->fileName.c_str(), std::ios::binary || std::ios::app);
		this->content.serializeToBinary(ofs);
	}
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