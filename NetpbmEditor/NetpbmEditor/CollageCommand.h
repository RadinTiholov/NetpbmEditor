#pragma once
#include "Command.h"

class CollageCommand : public Command
{
public:
	CollageCommand(const Direction& direction, const char* firstFileName, const char* secondFileName, const char* outFileName);
	void execute(Editor& editor) override;

	Command* clone() const override;
private:
	Direction direction;
	MyString firstFileName;
	MyString secondFileName;
	MyString outFileName;
	void setDirection(const Direction& direction);
};

