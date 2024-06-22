#pragma once
#include "UndoableCommand.h"

class GrayscaleCommand : public UndoableCommand
{
public:
	void execute(Session& session) override;

	Command* clone() const override;
	const char* name() override;
};

