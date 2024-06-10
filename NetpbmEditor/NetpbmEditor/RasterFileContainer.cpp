#include "RasterFileContainer.h"
#include <iostream>

RasterFileContainer::RasterFileContainer() 
{
	capacity = 8;
	data = new RasterFile * [capacity] { nullptr };
	size = 0;
}

RasterFileContainer::RasterFileContainer(const RasterFileContainer& other) 
{
	copyFrom(other);
}

RasterFileContainer::RasterFileContainer(RasterFileContainer&& other) noexcept 
{
	moveFrom(std::move(other));
}

RasterFileContainer& RasterFileContainer::operator=(const RasterFileContainer& other) 
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

RasterFileContainer& RasterFileContainer::operator=(RasterFileContainer&& other) noexcept 
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

RasterFileContainer::~RasterFileContainer() 
{
	free();
};

void RasterFileContainer::free() 
{
	for (int i = 0; i < size; i++)
		delete data[i];
	delete[] data;
}

void RasterFileContainer::copyFrom(const RasterFileContainer& other) 
{
	data = new RasterFile * [other.capacity];

	for (int i = 0; i < other.size; i++)
		data[i] = other.data[i]->clone();

	size = other.size;
	capacity = other.capacity;
}

void RasterFileContainer::moveFrom(RasterFileContainer&& other)
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	capacity = other.capacity;

	other.size = other.capacity = 0;
}

void RasterFileContainer::resize(size_t newCap)
{
	RasterFile** newData = new RasterFile* [newCap];
	for (int i = 0; i < size; i++)
		newData[i] = data[i];
	delete[] data;
	data = newData;
	capacity = newCap;
}

void RasterFileContainer::addFile(RasterFile* shape)
{
	if (size == capacity)
		resize(capacity * 2);
	data[size++] = shape;
	shape = nullptr;
}

void RasterFileContainer::addFile(const RasterFile& shape)
{
	RasterFile* cloned = shape.clone();
	addFile(cloned);
}

const RasterFile* RasterFileContainer::operator[](unsigned ind) const 
{
	return data[ind];
}

RasterFile* RasterFileContainer::operator[](unsigned ind)
{
	return data[ind];
}

unsigned RasterFileContainer::getSize() const 
{
	return this->size;
}