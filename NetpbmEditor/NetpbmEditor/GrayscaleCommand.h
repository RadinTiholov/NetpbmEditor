#pragma once
#include "Command.h"

class GrayscaleCommand : public Command 
{
public:
	void execute(Editor& editor) override;

	Command* clone() const override;
};

