#include "PGMFile.h"

PGMFile::PGMFile(unsigned magicNumber, unsigned width, unsigned height, Encoding encoding, const char* fileName, unsigned maxValue, Vector<uint16_t> values)
{
	setMagicNumber(magicNumber);
	setWidth(width);
	setHeigth(height);
	setMaxValue(maxValue);
	this->fileName = MyString(fileName);
	this->encoding = encoding;
	this->content = values;
}

void PGMFile::setMaxValue(unsigned maxValue)
{
	if (maxValue > 255)
	{
		throw std::invalid_argument(Constants::INVALID_MAXVALUE);
	}
	this->maxValue = maxValue;
}

RasterFile* PGMFile::clone() const
{
	return new PGMFile(*this);
}

void PGMFile::grayscale()
{

}

void PGMFile::monochrome()
{

};

void PGMFile::negative()
{

};

void PGMFile::rotate()
{

}

void PGMFile::serialize() const 
{
	std::ofstream ofs(this->fileName.c_str());
	if (!ofs.is_open())
	{
		throw std::runtime_error(Constants::COULD_NOT_OPEN_FILE_ERROR_MESSAGE);
	}
	this->writeMagicNumber(ofs);
	this->writeWidthAndHeight(ofs);
	ofs << '\n';
	this->writeMaxValue(ofs);
	if (this->encoding == Encoding::ASCII)
	{
		ofs << '\n';
		for (size_t i = 0; i < height * width; i++)
		{
			ofs << this->content[i] << ' ';
		}
	}
	else if (this->encoding == Encoding::Binary)
	{
		ofs.close();
		ofs.open(this->fileName.c_str(), std::ios::binary | std::ios::app);

	}
}

void PGMFile::writeMaxValue(std::ofstream& ofs) const
{
	ofs << this->maxValue << ' ';
}