#include "RotateCommand.h"

RotateCommand::RotateCommand(const Direction& direction) 
{
	setDirection(direction);
}

void RotateCommand::setDirection(const Direction& direction) 
{
	if (direction != Direction::Left && direction != Direction::Right)
	{
		throw std::invalid_argument("Invalid direction");
	}
	this->direction = direction;
}

void RotateCommand::execute(Editor& editor) 
{
	editor.sessions[editor.indexOfCurrentSession].rotate(this->direction);
}

Command* RotateCommand::clone() const
{
	return new RotateCommand(*this);
}