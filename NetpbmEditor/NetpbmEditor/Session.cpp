#include "Session.h"

unsigned Session::getId() const 
{
	return this->_id;
}

Session::Session(unsigned id) 
{
	this->_id = id;
}

void Session::addFile(RasterFile* file) 
{
	this->files.addFile(file);
}

void Session::grayScale() 
{
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		this->files[i]->grayscale();
	}
}

void Session::monochrome() 
{
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		this->files[i]->monochrome();
	}
}

void Session::negative() 
{
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		this->files[i]->negative();
	}
}

void Session::rotate(Direction direction)
{
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		this->files[i]->rotate(direction);
	}
}
