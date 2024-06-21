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