#include "NegativeCommand.h"
#include "Session.h"

void NegativeCommand::execute(Session& session)
{
	session.negative();
}

Command* NegativeCommand::clone() const 
{
	return new NegativeCommand(*this);
}

const char* NegativeCommand::name()
{
	return Constants::NEGATIVE_COMMAND;
}