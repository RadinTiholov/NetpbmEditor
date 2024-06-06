#pragma once
#include "Command.h"
#include "MyString.h"

class LoadCommand : public Command
{
	MyString fileName;
public:
	LoadCommand(const char* fileName);
	void execute(Editor& editor) override;

	Command* clone() const override;
};

