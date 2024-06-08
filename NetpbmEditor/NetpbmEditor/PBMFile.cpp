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
	//std::ofstream ofs(this->fileName.c_str());
	std::ofstream ofs("edno.pbm");
	if (!ofs.is_open())
	{
		throw std::runtime_error(Constants::COULD_NOT_OPEN_FILE_ERROR_MESSAGE);
	}
	this->content.print();
	
	this->writeMagicNumber(ofs);
	this->writeWidthAndHeight(ofs);
	//if (this->encoding == Encoding::ASCII)
	//{
	//	this->content.serializeToAscii(ofs);
	//}
	//else if(this->encoding == Encoding::Binary)
	//{
	
	//}

	ofs.close();
	//ofs.open(this->fileName.c_str(), std::ios::binary | std::ios::app);
	// 
	ofs.open("edno.pbm", std::ios::binary | std::ios::app);
	//this->content.serializeToBinary(ofs);

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
		if ((i + 1) % bytesPerRow == 0)
		{
			// byte with excess bits
			int mask = 128;
			for (int j = startBit; j < startBit + 8 - excessBits; j++)
			{
				if (this->content.contains(j))
				{
					bytes[i] |= mask;
				}
				mask >>= 1;
			}
			//
			for (int j = startBit + 8 - excessBits; j < startBit + 8; j++)
			{
				bytes[i] |= mask;
				mask >>= 1;
			}
			//
			startBit += 8 - excessBits;
		}
		else
		{
			// adjust the byte
			int mask = 128;
			for (int j = startBit; j < startBit + 8; j++)
			{
				if (this->content.contains(j))
				{
					bytes[i] |= mask;
				}
				mask >>= 1;
			}
			startBit += 8;
		}
	}
	ofs.write(reinterpret_cast<const char*>(bytes), neededBytes);
	delete[] bytes;
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