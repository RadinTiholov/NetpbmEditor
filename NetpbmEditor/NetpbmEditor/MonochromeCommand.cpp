#include "MonochromeCommand.h"

void MonochromeCommand::execute(Editor& editor)
{
	editor.sessions[editor.indexOfCurrentSession].monochrome();
};

Command* MonochromeCommand::clone() const 
{
	return new MonochromeCommand(*this);
};