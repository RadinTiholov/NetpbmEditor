#pragma once

class RasterFile 
{
public:
	virtual RasterFile* clone() const = 0;
};
