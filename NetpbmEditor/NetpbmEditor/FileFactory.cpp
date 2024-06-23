#include "FileFactory.h"

static bool canContainExcessBits(int currentByte, int bytesPerRow)
{
	return currentByte % bytesPerRow == 0;
}

static void extractBitsFromByteWithExcessBits(int& index, int currentByte, const uint8_t* rawBytes, DynamicSet& bitset, int excessBits) 
{
	int mask = 128;
	for (int j = index; j < index + 8 - excessBits; j++)
	{
		if (mask & rawBytes[currentByte])
		{
			bitset.add(j);
		}
		mask >>= 1;
	}
	index += 8 - excessBits;
}

static void extractBitsFromByteWithoutExcessBits(int& index, int currentByte, const uint8_t* rawBytes, DynamicSet& bitset)
{
	int mask = 128;
	for (int j = index; j < index + 8; j++)
	{
		if (mask & rawBytes[currentByte])
		{
			bitset.add(j);
		}
		mask >>= 1;
	}
	index += 8;
}

static void extractLine(DynamicSet& bitset, const char* line, unsigned& index) 
{
	while (*line)
	{
		if (*line == '0')
		{
			index++;
		}
		else if (*line == '1')
		{
			bitset.add(index++);
		}
		line++;
	}
}

static int charToNumber(char c) {
	if (c >= '0' && c <= '9') 
	{
		return c - '0';
	}
	return -1;
}

PBMFile* FileFactory::createPBMASCIIFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName)
{
	DynamicSet bitset(height * width);
	unsigned index = 0;
	while (!ifs.eof())
	{
		char buffer[4096];
		ifs.getline(buffer, 4096);
		extractLine(bitset, buffer, index);
	}
	PBMFile* file = new PBMFile(magicNumber, width, height, Encoding::ASCII, fileName, bitset);
	return file;
}

PBMFile* FileFactory::createPBMBinaryFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName) 
{
	size_t startPosition = ifs.tellg();
	ifs.close();
	ifs.open(fileName, std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::runtime_error(Constants::COULD_NOT_OPEN_FILE_ERROR_MESSAGE);
	}
	ifs.seekg(startPosition);

	DynamicSet bitset(height * width);

	int bytesPerRow = width / 8;
	int excessBits = 0;
	if (width % 8 != 0)
	{
		bytesPerRow += 1;
		excessBits = 8 - width % 8;
	}
	int neededBytes = bytesPerRow * height;
	uint8_t* rawBytes = new uint8_t[neededBytes];
	ifs.read((char*)rawBytes, neededBytes);

	// Parse to dynamic set
	int index = 0;
	for (size_t i = 0; i < neededBytes; i++)
	{
		if (canContainExcessBits(i + 1, bytesPerRow))
		{
			extractBitsFromByteWithExcessBits(index, i, rawBytes, bitset, excessBits);
		}
		else
		{
			extractBitsFromByteWithoutExcessBits(index, i, rawBytes, bitset);
		}
	}
	PBMFile* file = new PBMFile(magicNumber, width, height, Encoding::Binary, fileName, bitset);
	delete[] rawBytes;
	return file;
}

PGMFile* FileFactory::createPGMASCIIFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName)
{
	unsigned maxValue;
	ifs >> maxValue;
	Vector<uint16_t> values(height * width); // We set the expected capacity and do not resize
	for (size_t i = 0; i < height * width; i++)
	{
		uint16_t value;
		ifs >> value;
		values.pushBack(value);
	}
	PGMFile* file = new PGMFile(magicNumber, width, height, Encoding::ASCII, fileName, maxValue, values);
	//PGMFile* file = new PGMFile(5, width, height, Encoding::Binary, fileName, maxValue, values);
	return file;
}

PGMFile* FileFactory::createPGMBinaryFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName) 
{
	unsigned maxValue;
	ifs >> maxValue;
	Vector<uint16_t> values(height * width); // We set the expected capacity and do not resize
	if (maxValue <= UINT8_MAX)
	{
		for (size_t i = 0; i < height * width; i++)
		{
			uint8_t value;
			ifs.read((char*)(&value), sizeof(uint8_t));
			values.pushBack(value);
		}
	}
	else
	{
		for (size_t i = 0; i < height * width; i++)
		{
			uint16_t value;
			ifs.read((char*)(&value), sizeof(uint16_t));
			values.pushBack(value);
		}
	}
	PGMFile* file = new PGMFile(magicNumber, width, height, Encoding::Binary, fileName, maxValue, values);
	return file;
}

PPMFile* FileFactory::createPPMASCIIFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName)
{
	unsigned maxValue;
	ifs >> maxValue;
	Vector<RGBData> values(height * width);

	for (size_t i = 0; i < height * width; i++)
	{
		uint16_t red;
		uint16_t green;
		uint16_t blue;
		ifs >> red;
		ifs >> green;
		ifs >> blue;
		values.pushBack(RGBData(red, green, blue));
	}

	PPMFile* file = new PPMFile(magicNumber, width, height, Encoding::ASCII, fileName, maxValue, values);
	//PPMFile* file = new PPMFile(6, width, height, Encoding::Binary, fileName, maxValue, values);
	return file;
}

PPMFile* FileFactory::createPPMBinaryFile(int height, int width, int magicNumber, std::ifstream& ifs, const char* fileName)
{
	unsigned maxValue;
	ifs >> maxValue;
	Vector<RGBData> values(height * width);

	if (maxValue <= UINT8_MAX)
	{
		for (size_t i = 0; i < height * width; i++)
		{
			uint8_t rgbValues[3];
			ifs.read((char*)(rgbValues), sizeof(uint8_t) * 3);
			values.pushBack(RGBData(rgbValues[0], rgbValues[1], rgbValues[2]));
		}
	}
	else
	{
		for (size_t i = 0; i < height * width; i++)
		{
			uint16_t rgbValues[3];
			ifs.read((char*)(rgbValues), sizeof(uint16_t) * 3);
			values.pushBack(RGBData(rgbValues[0], rgbValues[1], rgbValues[2]));
		}
	}
	PPMFile* file = new PPMFile(magicNumber, width, height, Encoding::Binary, fileName, maxValue, values);
	return file;
}

RasterFile* FileFactory::createFile(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		throw std::runtime_error(Constants::COULD_NOT_OPEN_FILE_ERROR_MESSAGE);
	}
	char magicNumber[256];
	ifs >> magicNumber;
	int width;
	int height;
	ifs >> width;
	ifs >> height;
	ifs.ignore();

	if (std::strlen(magicNumber) != 2)
	{
		throw std::runtime_error(Constants::COULD_NOT_OPEN_FILE_ERROR_MESSAGE);
	}

	switch (magicNumber[1])
	{
	case '1':
	{
		return createPBMASCIIFile(height, width, charToNumber(magicNumber[1]), ifs, fileName);
	}
	case '2':
	{
		return createPGMASCIIFile(height, width, charToNumber(magicNumber[1]), ifs, fileName);
	}
	case '3':
	{
		return createPPMASCIIFile(height, width, charToNumber(magicNumber[1]), ifs, fileName);
	}
	case '4':
	{
		return createPBMBinaryFile(height, width, charToNumber(magicNumber[1]), ifs, fileName);
	}
	case '5':
	{
		return createPGMBinaryFile(height, width, charToNumber(magicNumber[1]), ifs, fileName);
	}
	case '6':
	{
		return createPPMBinaryFile(height, width, charToNumber(magicNumber[1]), ifs, fileName);
	}
	default:
		break;
	}
}