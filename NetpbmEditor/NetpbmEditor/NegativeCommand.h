#pragma once
#include "Command.h"
class NegativeCommand : public Command
{
public:
	void execute(Editor& editor) override;

	Command* clone() const override;
};

