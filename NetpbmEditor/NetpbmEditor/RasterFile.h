#pragma once
#include "MyString.h"
#include "Constants.h"
#include <fstream>

enum class Encoding 
{
	ASCII,
	Binary
};

class RasterFile 
{
protected:
	unsigned magicNumber;
	unsigned width;
	unsigned height;
	Encoding encoding;
	MyString fileName;

	void setMagicNumber(unsigned newMagicNumber);
	void setWidth(unsigned newWidth);
	void setHeigth(unsigned newHeight);
public:
	virtual void grayscale() = 0;
	virtual void monochrome() = 0;
	virtual void negative() = 0;
	virtual void rotate() = 0; //TODO: add direction

	void writeMagicNumber(std::ofstream& is) const;
	void writeWidthAndHeight(std::ofstream& is) const;
	virtual RasterFile* clone() const = 0;
	virtual void serialize() const = 0;
	virtual ~RasterFile() = default;
};
