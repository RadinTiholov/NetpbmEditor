#pragma once

class RasterFile 
{
public:
	virtual void grayscale() = 0;
	virtual void monochrome() = 0;
	virtual void negative() = 0;
	virtual void rotate() = 0; //TODO: add direction

	virtual RasterFile* clone() const = 0;
	virtual ~RasterFile() = default;
};
