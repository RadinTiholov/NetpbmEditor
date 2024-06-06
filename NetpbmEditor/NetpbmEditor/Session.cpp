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
	//Here we apply grayScale for all files
}

void Session::monochrome() 
{
	//Here we apply monochrome for all files
}