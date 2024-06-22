#pragma once
#include "MyString.h"
#include "Constants.h"
#include <fstream>
#include <iostream>
#include "Direction.h"

class PBMFile;
class PGMFile;
class PPMFile;

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
	void setFileName(const char* fileName);
	unsigned getWidth() const;
	unsigned getHeight() const;
	virtual RasterFile* clone() const = 0;
	virtual void serialize() const = 0;
	virtual ~RasterFile() = default;

	virtual RasterFile* horizontalCollageWithPBM(const PBMFile* other, const char* fileName) const = 0;
	virtual RasterFile* horizontalCollageWithPGM(const PGMFile* other, const char* fileName) const = 0;
	virtual RasterFile* horizontalCollageWithPPM(const PPMFile* other, const char* fileName) const = 0;
	virtual RasterFile* verticalCollageWithPBM(const PBMFile* other, const char* fileName) const = 0;
	virtual RasterFile* verticalCollageWithPGM(const PGMFile* other, const char* fileName) const = 0;
	virtual RasterFile* verticalCollageWithPPM(const PPMFile* other, const char* fileName) const = 0;
};
