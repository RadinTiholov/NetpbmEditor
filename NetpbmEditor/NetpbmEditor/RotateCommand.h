#pragma once
#include "UndoableCommand.h"
#include "Direction.h"

class RotateCommand: public UndoableCommand
{
public:
	RotateCommand(const Direction& direction);
	void execute(Session& session) override;

	Command* clone() const override;
	const char* name() override;
private:
	Direction direction;
	void setDirection(const Direction& direction);
};

