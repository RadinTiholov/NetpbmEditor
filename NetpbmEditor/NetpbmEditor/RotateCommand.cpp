#include "RotateCommand.h"
#include "Session.h"

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

void RotateCommand::execute(Session& session)
{
	session.rotate(this->direction);
}

Command* RotateCommand::clone() const
{
	return new RotateCommand(*this);
}

const char* RotateCommand::name()
{
	return this->direction == Direction::Left ? "rotate left" : "rotate right";
}