#pragma once
#include "UndoableCommand.h"

class NegativeCommand : public UndoableCommand
{
public:
	void execute(Session& session) override;

	Command* clone() const override;
};

