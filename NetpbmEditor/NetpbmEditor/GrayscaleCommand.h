#pragma once
#include "UndoableCommand.h"

class GrayscaleCommand : public UndoableCommand
{
public:
	void execute(Editor& editor) override;

	Command* clone() const override;
};

