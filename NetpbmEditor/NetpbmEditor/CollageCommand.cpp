#include "CollageCommand.h"

CollageCommand::CollageCommand(const Direction& direction, const char* firstFileName, const char* secondFileName, const char* outFileName)
{
	setDirection(direction);
	this->firstFileName = firstFileName;
	this->secondFileName = secondFileName;
	this->outFileName = outFileName;
}

void CollageCommand::execute(Editor& editor)
{
	int firstImageIndex = editor.findFileIndexInCurrentSessionByName(firstFileName.c_str());
	int secondImageIndex = editor.findFileIndexInCurrentSessionByName(secondFileName.c_str());
	if (firstImageIndex == -1 || secondImageIndex == -1)
	{
		// TODO: Some exception here
	}
	unsigned firstWidth = editor.sessions[editor.indexOfCurrentSession].files[firstImageIndex]->getWidth();
	unsigned firstHeight = editor.sessions[editor.indexOfCurrentSession].files[firstImageIndex]->getHeight();
	unsigned secondWidth = editor.sessions[editor.indexOfCurrentSession].files[secondImageIndex]->getWidth();
	unsigned secondHeight = editor.sessions[editor.indexOfCurrentSession].files[secondImageIndex]->getHeight();
	if (firstWidth != secondWidth || firstHeight != secondHeight)
	{
		// TODO: Some exception here
	}
	editor.collage(direction, firstImageIndex, secondImageIndex, outFileName.c_str());
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