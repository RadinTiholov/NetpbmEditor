#include "GrayscaleCommand.h"

void GrayscaleCommand::execute(Editor& editor)
{
	editor.sessions[editor.indexOfCurrentSession].grayScale();
}

Command* GrayscaleCommand::clone() const
{
	return new GrayscaleCommand(*this);
}