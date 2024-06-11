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
	if (maxValue > INT16_MAX)
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
	for (size_t i = 0; i < this->content.getSize(); i++)
	{
		this->content[i] = this->maxValue * std::round((double)this->content[i] / this->maxValue);
	}
	std::cout << "Monochrome applied" << std::endl;
};

void PGMFile::negative()
{
	for (size_t i = 0; i < this->content.getSize(); i++)
	{
		this->content[i] = this->maxValue - this->content[i];
	}
	std::cout << "Negative applied" << std::endl;
};

void PGMFile::rotate(Direction direction)
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
}

void PGMFile::rotateRight() 
{
	Vector<uint16_t> newContent(this->height * this->width);

	for (int col = 0; col < width; col++)
	{
		for (int row = height - 1; row >= 0; row--)
		{
			newContent.pushBack(this->content[row * width + col]);
		}
	}

	this->content = newContent;
}

void PGMFile::rotateLeft()
{
	Vector<uint16_t> newContent(this->height * this->width);

	for (int col = width - 1; col >= 0; col--)
	{
		for (int row = 0; row < height; row++)
		{
			newContent.pushBack(this->content[row * width + col]);
		}
	}

	this->content = newContent;
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
		this->serializeContentToBinary(ofs);
		ofs.close();
	}
}

void PGMFile::serializeContentToBinary(std::ofstream& ofs) const 
{
	size_t size = this->content.getSize();

	if (this->maxValue <= UINT8_MAX)
	{
		for (size_t i = 0; i < size; i++)
		{
			uint8_t value = this->content[i];
			ofs.write(reinterpret_cast<const char*>(&value), sizeof(uint8_t));
		}
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			uint16_t value = this->content[i];
			ofs.write(reinterpret_cast<const char*>(&value), sizeof(uint16_t));
		}
	}
}

void PGMFile::writeMaxValue(std::ofstream& ofs) const
{
	ofs << this->maxValue << ' ';
}