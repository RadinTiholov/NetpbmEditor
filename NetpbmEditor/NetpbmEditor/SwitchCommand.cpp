#include "SwitchCommand.h"

SwitchCommand::SwitchCommand(int id)
{
	this->id = id;
}

void SwitchCommand::execute(Editor& editor)
{
	try
	{
		editor.setIndexOfCurrentSession(id);
		std::cout << Constants::SWITCH_MESSAGE << id << std::endl;
	}
	catch (const std::invalid_argument&)
	{
		std::cout << Constants::INVALID_SWITCH_MESSAGE;
	}
};

Command* SwitchCommand::clone() const
{
	return new SwitchCommand(*this);
}