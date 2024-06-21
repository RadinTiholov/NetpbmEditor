#pragma once
#include "UndoableCommand.h"

class NegativeCommand : public UndoableCommand
{
public:
	void execute(Editor& editor) override;

	Command* clone() const override;
};

