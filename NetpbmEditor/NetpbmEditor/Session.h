#pragma once
#include "RasterFile.h"
#include "Transformation.h"
#include "RasterFileContainer.h"
#include "TransformationContainer.h"

class Session
{
public:
	Session() = default;
	Session(unsigned id);
	unsigned getId() const;
	void addFile(RasterFile* file);
private:
	unsigned _id = 0;
	RasterFileContainer files;
	TransformationContainer transformations;
};

