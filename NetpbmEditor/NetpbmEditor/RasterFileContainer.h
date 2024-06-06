#pragma once
#include "RasterFile.h"

class RasterFileContainer
{
public:
	RasterFileContainer();
	RasterFileContainer(const RasterFileContainer& other);
	RasterFileContainer(RasterFileContainer&& other) noexcept;
	RasterFileContainer& operator=(const RasterFileContainer& other);
	RasterFileContainer& operator=(RasterFileContainer&& other) noexcept;
	~RasterFileContainer();

	void addFile(RasterFile* shape); //will take the ownership of the object  

	void addFile(const RasterFile& shape);

	const RasterFile* operator[](unsigned) const;
	unsigned getSize() const;
private:
	void free();
	void copyFrom(const RasterFileContainer& other);
	void moveFrom(RasterFileContainer&& other);

	void resize(size_t newCap);

	RasterFile** data = nullptr;
	size_t capacity = 0;
	size_t size = 0;
};

