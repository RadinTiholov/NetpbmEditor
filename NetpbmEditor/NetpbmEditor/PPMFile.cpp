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
	for (size_t i = 0; i < this->content.getSize(); i++)
	{
		uint16_t newValue = std::round((double)(this->content[i].red + this->content[i].green + this->content[i].blue) / (3 * this->maxValue));
		this->content[i].red = newValue * this->maxValue;
		this->content[i].green = newValue * this->maxValue;
		this->content[i].blue = newValue * this->maxValue;
	}
	std::cout << "Monochrome applied" << std::endl;
};

void PPMFile::negative() 
{
	for (size_t i = 0; i < this->content.getSize(); i++)
	{
		this->content[i].red = this->maxValue - this->content[i].red;
		this->content[i].green = this->maxValue - this->content[i].green;
		this->content[i].blue = this->maxValue - this->content[i].blue;
	}
	std::cout << "Negative applied" << std::endl;
};

void PPMFile::rotateRight()
{
	Vector<RGBData> newContent(this->height * this->width);

	for (int col = 0; col < width; col++)
	{
		for (int row = height - 1; row >= 0; row--)
		{
			newContent.pushBack(this->content[row * width + col]);
		}
	}

	this->content = newContent;
}

void PPMFile::rotateLeft()
{
	Vector<RGBData> newContent(this->height * this->width);

	for (int col = width - 1; col >= 0; col--)
	{
		for (int row = 0; row < height; row++)
		{
			newContent.pushBack(this->content[row * width + col]);
		}
	}

	this->content = newContent;
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

RasterFile* PPMFile::horizontalCollage(const RasterFile* other, const char* fileName) const 
{
	return other->horizontalCollageWithPPM(this, fileName);
}

RasterFile* PPMFile::verticalCollage(const RasterFile* other, const char* fileName) const 
{
	return other->verticalCollageWithPPM(this, fileName);
}

RasterFile* PPMFile::horizontalCollageWithPBM(const PBMFile* other, const char* fileName) const 
{
	throw std::logic_error(Constants::COLLAGE_MESSAGE);
}

RasterFile* PPMFile::horizontalCollageWithPGM(const PGMFile* other, const char* fileName) const 
{
	throw std::logic_error(Constants::COLLAGE_MESSAGE);
}

RasterFile* PPMFile::horizontalCollageWithPPM(const PPMFile* other, const char* newFileName) const 
{
	Vector<RGBData> values(2 * this->height * this->width);

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			values.pushBack(this->content[i * width + j]);
		}
		for (size_t j = 0; j < width; j++)
		{
			values.pushBack(this->content[i * width + j]);
		}
	}
	std::cout << "Collage applied!" << std::endl;
	return new PPMFile(this->magicNumber, 2* this->width, this->height, this->encoding, newFileName, this->maxValue, values);
}

RasterFile* PPMFile::verticalCollageWithPBM(const PBMFile* other, const char* fileName) const 
{
	throw std::logic_error(Constants::COLLAGE_MESSAGE);
}

RasterFile* PPMFile::verticalCollageWithPGM(const PGMFile* other, const char* fileName) const 
{
	throw std::logic_error(Constants::COLLAGE_MESSAGE);
}

RasterFile* PPMFile::verticalCollageWithPPM(const PPMFile* other, const char* newFileName) const
{
	Vector<RGBData> values(2 * this->height * this->width);

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			values.pushBack(this->content[i * width + j]);
		}
	}

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			values.pushBack(this->content[i * width + j]);
		}
	}

	return new PPMFile(this->magicNumber, this->width, 2 * this->height, this->encoding, newFileName, this->maxValue, values);
}