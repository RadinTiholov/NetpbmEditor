#pragma once
#include "UndoableCommand.h"

class MonochromeCommand : public UndoableCommand
{
public:
	void execute(Editor& editor) override;

	Command* clone() const override;
};

