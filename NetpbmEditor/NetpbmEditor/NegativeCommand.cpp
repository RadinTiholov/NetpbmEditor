#include "NegativeCommand.h"

void NegativeCommand::execute(Editor& editor) 
{
	editor.sessions[editor.indexOfCurrentSession].negative();
}

Command* NegativeCommand::clone() const 
{
	return new NegativeCommand(*this);
}