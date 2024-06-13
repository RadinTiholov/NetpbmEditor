#pragma once
#include "MyString.h"
#include "Constants.h"
#include <fstream>
#include <iostream>
#include "Direction.h"

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

	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;

	virtual RasterFile* horizontalCollage(const RasterFile* other, const char* fileName) const = 0;
	virtual RasterFile* verticalCollage(const RasterFile* other, const char* fileName) const = 0;
public:
	virtual void grayscale() = 0;
	virtual void monochrome() = 0;
	virtual void negative() = 0;
	RasterFile* collageWith(const Direction& direction, const RasterFile* other, const char* fileName) const;
	void rotate(Direction direction);

	void writeMagicNumber(std::ofstream& is) const;
	void writeWidthAndHeight(std::ofstream& is) const;
	const char* getFileName() const;
	unsigned getWidth() const;
	unsigned getHeight() const;
	virtual RasterFile* clone() const = 0;
	virtual void serialize() const = 0;
	virtual ~RasterFile() = default;
};
