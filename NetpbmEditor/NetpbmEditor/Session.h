#pragma once
#include "RasterFile.h"
#include "RasterFileContainer.h"
#include "Direction.h"

class Session
{
public:
	Session() = default;
	Session(unsigned id);
	unsigned getId() const;
	void addFile(RasterFile* file);

	void grayScale();
	void monochrome();
	void negative();
	void rotate(const Direction& direction);
	RasterFile* collage(const Direction& direction, int indexOfFirst, int indexOfSecond, const char* outFileName);

	friend class Editor;
	friend class CollageCommand;
private:
	unsigned _id = 0;
	RasterFileContainer files;
};

