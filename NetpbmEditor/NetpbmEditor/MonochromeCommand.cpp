#include "MonochromeCommand.h"
#include "Session.h"

void MonochromeCommand::execute(Session& session)
{
	session.monochrome();
};

Command* MonochromeCommand::clone() const 
{
	return new MonochromeCommand(*this);
};

const char* MonochromeCommand::name()
{
	return Constants::MONOCHROME_COMMAND;
}