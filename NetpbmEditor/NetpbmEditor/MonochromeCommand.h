#pragma once
#include "UndoableCommand.h"

class MonochromeCommand : public UndoableCommand
{
public:
	void execute(Session& session) override;

	Command* clone() const override;
};

