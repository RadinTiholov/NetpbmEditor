#include "SwitchCommand.h"

SwitchCommand::SwitchCommand(int id)
{
	this->id = id;
}

void SwitchCommand::execute(Editor& editor)
{
	// TODO: Change when you implement ex handling
	try
	{
		editor.setIndexOfCurrentSession(id);
		std::cout << Constants::SWITCH_COMMAND + id << std::endl;
	}
	catch (const std::invalid_argument&)
	{
		std::cout << Constants::INVALID_INDEX_ERROR_MESSAGE;
	}
};

Command* SwitchCommand::clone() const
{
	return new SwitchCommand(*this);
}