#pragma once
#include "UndoableCommand.h"

class CollageCommand : public UndoableCommand
{
public:
	CollageCommand(const Direction& direction, const char* firstFileName, const char* secondFileName, const char* outFileName);
	void execute(Session& session) override;

	Command* clone() const override;
private:
	Direction direction;
	MyString firstFileName;
	MyString secondFileName;
	MyString outFileName;
	void setDirection(const Direction& direction);
};

