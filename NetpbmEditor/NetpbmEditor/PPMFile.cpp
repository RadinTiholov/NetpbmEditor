#include "PPMFile.h"

PPMFile::PPMFile(unsigned magicNumber, unsigned width, unsigned height, Encoding encoding, const char* fileName, unsigned maxValue, Vector<RGBData> values)
{
	setMagicNumber(magicNumber);
	setWidth(width);
	setHeigth(height);
	setMaxValue(maxValue);
	this->fileName = MyString(fileName);
	this->encoding = encoding;
	this->content = values;
}

void PPMFile::setMaxValue(unsigned maxValue)
{
	if (maxValue > INT16_MAX)
	{
		throw std::invalid_argument(Constants::INVALID_MAXVALUE);
	}
	this->maxValue = maxValue;
}

void PPMFile::writeMaxValue(std::ofstream& ofs) const
{
	ofs << this->maxValue << ' ';
}

RasterFile* PPMFile::clone() const 
{
	return new PPMFile(*this);
}

void PPMFile::grayscale()
{
	for (size_t i = 0; i < this->content.getSize(); i++)
	{
		uint16_t grayscale = Constants::GRAYSCALE_RED * this->content[i].red + Constants::GRAYSCALE_GREEN * this->content[i].green + Constants::GRAYSCALE_BLUE * this->content[i].blue;
		this->content[i].red = grayscale;
		this->content[i].green = grayscale;
		this->content[i].blue = grayscale;
	}
	std::cout << "Grayscale applied" << std::endl;
}

void PPMFile::monochrome() 
{

};

void PPMFile::negative() 
{

};

void PPMFile::rotate() 
{

}

void PPMFile::serialize() const
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
			ofs << this->content[i].red << ' ' << this->content[i].green << ' ' << this->content[i].blue << ' ';
		}
	}
	else if (this->encoding == Encoding::Binary)
	{
		ofs.close();
		ofs.open(this->fileName.c_str(), std::ios::binary | std::ios::app);
		this->serializeContentToBinary(ofs);
		ofs.close();
	}
}

void PPMFile::serializeContentToBinary(std::ofstream& ofs) const
{
	size_t size = this->content.getSize();

	if (this->maxValue <= UINT8_MAX)
	{
		for (size_t i = 0; i < size; i++)
		{
			uint8_t pixel[3];
			pixel[0] = this->content[i].red;
			pixel[1] = this->content[i].green;
			pixel[2] = this->content[i].blue;
			ofs.write(reinterpret_cast<const char*>(pixel), sizeof(uint8_t) * 3);
		}
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			uint16_t pixel[3];
			pixel[0] = this->content[i].red;
			pixel[1] = this->content[i].green;
			pixel[2] = this->content[i].blue;
			ofs.write(reinterpret_cast<const char*>(pixel), sizeof(uint16_t) * 3);
		}
	}
}