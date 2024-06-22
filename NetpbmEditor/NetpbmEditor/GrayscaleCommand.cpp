#include "GrayscaleCommand.h"
#include "Session.h"

void GrayscaleCommand::execute(Session& session)
{
	session.grayScale();
}

Command* GrayscaleCommand::clone() const
{
	return new GrayscaleCommand(*this);
}

const char* GrayscaleCommand::name()
{
	return Constants::GRAYSCALE_COMMAND;
}