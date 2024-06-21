#pragma once
#include "Command.h"
#include "Constants.h"

class SwitchCommand : public Command
{
public:
	SwitchCommand(int id);
	void execute(Editor& editor) override;

	Command* clone() const override;
private:
	int id;
};

