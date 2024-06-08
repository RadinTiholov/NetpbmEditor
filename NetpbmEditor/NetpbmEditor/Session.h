#pragma once
#include "RasterFile.h"
#include "RasterFileContainer.h"

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
	void rotate(); // TODO: direction

	friend class Editor;
private:
	unsigned _id = 0;
	RasterFileContainer files;
};

