#include "CollageCommand.h"
#include "Session.h"

CollageCommand::CollageCommand(const Direction& direction, const char* firstFileName, const char* secondFileName, const char* outFileName)
{
	setDirection(direction);
	this->firstFileName = firstFileName;
	this->secondFileName = secondFileName;
	this->outFileName = outFileName;
}

void CollageCommand::execute(Session& session)
{
	int firstImageIndex = session.findFileIndexByName(firstFileName.c_str());
	int secondImageIndex = session.findFileIndexByName(secondFileName.c_str());
	if (firstImageIndex == -1 || secondImageIndex == -1)
	{
		// TODO: Some exception here
	}
	unsigned firstWidth = session.files[firstImageIndex]->getWidth();
	unsigned firstHeight = session.files[firstImageIndex]->getHeight();
	unsigned secondWidth = session.files[secondImageIndex]->getWidth();
	unsigned secondHeight = session.files[secondImageIndex]->getHeight();
	if (firstWidth != secondWidth || firstHeight != secondHeight)
	{
		// TODO: Some exception here
	}
	RasterFile* file = session.collage(direction, firstImageIndex, secondImageIndex, this->outFileName.c_str());

	session.addFile(file);
}

void CollageCommand::setDirection(const Direction& direction)
{
	if (direction != Direction::Horizontal && direction != Direction::Vertical)
	{
		throw std::invalid_argument("Invalid direction");
	}
	this->direction = direction;
}

Command* CollageCommand::clone() const 
{
	return new CollageCommand(*this);
}