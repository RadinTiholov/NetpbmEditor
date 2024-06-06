#include "FileFactory.h"

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
	//TODO: Think about the comments
	if (std::strlen(magicNumber) != 2)
	{
		throw std::runtime_error(Constants::COULD_NOT_OPEN_FILE_ERROR_MESSAGE);
	}

	switch (magicNumber[1])
	{
	case '1':
		// read the bits

		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		ifs.close();
		break;
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