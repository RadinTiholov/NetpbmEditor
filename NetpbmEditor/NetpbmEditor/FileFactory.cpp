#include "FileFactory.h"

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
	//TODO: Think about the comments
	if (std::strlen(magicNumber) != 2)
	{
		throw std::runtime_error(Constants::COULD_NOT_OPEN_FILE_ERROR_MESSAGE);
	}

	switch (magicNumber[1])
	{
	case '1':
	{
		DynamicSet bitset(height * width);
		unsigned index = 0;
		while (!ifs.eof())
		{
			char buffer[4096];
			ifs.getline(buffer, 4096);
			extractLine(bitset, buffer, index);
		}
		PBMFile* file = new PBMFile(charToNumber(magicNumber[1]), width, height, Encoding::ASCII, fileName, bitset);
		return file;
	}
	case '2':
		break;
	case '3':
		break;
	case '4':
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
			if ((i + 1) % bytesPerRow == 0)
			{
				int mask = 128;
				for (int j = index; j < index + 8 - excessBits; j++)
				{
					if (mask & rawBytes[i])
					{
						bitset.add(j);
					}
					mask >>= 1;
				}
				index += 8 - excessBits;
			}
			else 
			{
				int mask = 128;
				for (int j = index; j < index + 8; j++)
				{
					if (mask & rawBytes[i])
					{
						bitset.add(j);
					}
					mask >>= 1;
				}
				index += 8;
			}
		}
		PBMFile* file = new PBMFile(charToNumber(magicNumber[1]), width, height, Encoding::Binary, fileName, bitset);
		delete[] rawBytes;
		return file;
	}
	case '5':
		ifs.close();
		break;
	case '6':
		ifs.close();
		break;
	default:
		break;
	}
}