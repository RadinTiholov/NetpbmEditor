#pragma once
#include "Command.h"
#include "Direction.h"

class RotateCommand: public Command
{
public:
	RotateCommand(const Direction& direction);
	void execute(Editor& editor) override;

	Command* clone() const override;
private:
	Direction direction;
	void setDirection(const Direction& direction);
};

