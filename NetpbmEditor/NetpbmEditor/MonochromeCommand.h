#pragma once
#include "Command.h"

class MonochromeCommand : public Command
{
public:
	void execute(Editor& editor) override;

	Command* clone() const override;
};

