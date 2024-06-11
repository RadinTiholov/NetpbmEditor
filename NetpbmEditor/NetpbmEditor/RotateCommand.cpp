#include "RotateCommand.h"

RotateCommand::RotateCommand(Direction direction) 
{
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