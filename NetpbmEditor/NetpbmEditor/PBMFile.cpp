#include "PBMFile.h"

static bool canContainExcessBits(int currentByte, int bytesPerRow)
{
	return currentByte % bytesPerRow == 0;
}

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
		ofs << '\n';
		this->content.serializeToAscii(ofs);
	}
	else if (this->encoding == Encoding::Binary)
	{
		ofs.close();
		ofs.open(this->fileName.c_str(), std::ios::binary | std::ios::app);

		this->serializeContentToBinary(ofs);
		ofs.close();
	}
}

void PBMFile::serializeContentToBinary(std::ofstream& ofs) const
{
	int bytesPerRow = width / 8;
	int excessBits = 0;
	if (width % 8 != 0)
	{
		bytesPerRow += 1;
		excessBits = 8 - width % 8;
	}
	int neededBytes = bytesPerRow * height;
	uint8_t* bytes = new uint8_t[neededBytes]{ 0 };

	int startBit = 0;
	for (int i = 0; i < neededBytes; i++)
	{
		if (canContainExcessBits(i + 1, bytesPerRow))
		{
			adjustByteWithExcessBits(startBit, bytes, excessBits, i);
		}
		else
		{
			adjustByteWithoutExcessBits(startBit, bytes, i);
		}
	}
	ofs.write(reinterpret_cast<const char*>(bytes), neededBytes);
	delete[] bytes;
}

void PBMFile::adjustByteWithoutExcessBits(int& startBit, uint8_t*& bytes, int currentByteIndex) const
{
	int mask = 128;
	for (int j = startBit; j < startBit + 8; j++)
	{
		if (this->content.contains(j))
		{
			bytes[currentByteIndex] |= mask;
		}
		mask >>= 1;
	}
	startBit += 8;
}

void PBMFile::adjustByteWithExcessBits(int& startBit, uint8_t*& bytes, int excessBits, int currentByteIndex) const
{
	int mask = 128;
	for (int j = startBit; j < startBit + 8 - excessBits; j++)
	{
		if (this->content.contains(j))
		{
			bytes[currentByteIndex] |= mask;
		}
		mask >>= 1;
	}
	for (int j = startBit + 8 - excessBits; j < startBit + 8; j++)
	{
		bytes[currentByteIndex] |= mask;
		mask >>= 1;
	}
	startBit += 8 - excessBits;
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