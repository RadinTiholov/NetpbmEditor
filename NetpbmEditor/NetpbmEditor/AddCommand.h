#pragma once
#include "Command.h"

class AddCommand : public Command
{
	MyString fileName;
public:
	AddCommand(const char* fileName);
	void execute(Session& session) override;

	const char* getFileName() const;
	Command* clone() const override;
	const char* name() override;
};

