#pragma once
#include "UndoableCommand.h"
#include "Direction.h"

class RotateCommand: public UndoableCommand
{
public:
	RotateCommand(const Direction& direction);
	void execute(Session& session) override;

	Command* clone() const override;
private:
	Direction direction;
	void setDirection(const Direction& direction);
};

