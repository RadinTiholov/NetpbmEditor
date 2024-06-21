#pragma once
#include "Command.h"

class AddCommand : public Command
{
	MyString fileName;
public:
	AddCommand(const char* fileName);
	void execute(Session& session) override;

	Command* clone() const override;
};

