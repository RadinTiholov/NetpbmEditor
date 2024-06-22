#include "Editor.h"

void Editor::setIndexOfCurrentSession(int newIndex) 
{
	if (newIndex < 0 || newIndex >= this->sessions.getSize())
	{
		throw std::invalid_argument(Constants::INVALID_INDEX_ERROR_MESSAGE);
	}
	this->indexOfCurrentSession = newIndex;
}

void Editor::checkForActiveSession() const 
{
	if (indexOfCurrentSession == -1)
	{
		throw std::logic_error(Constants::INVALID_SESSION_ERROR_MESSAGE);
	}
}

void Editor::saveAs(const char* newFileName)
{
	checkForActiveSession();
}

void Editor::save() 
{
	checkForActiveSession();

	this->sessions[indexOfCurrentSession].executeAllCommands();
	this->sessions[indexOfCurrentSession].serializeAllFiles();
	this->sessions[indexOfCurrentSession].removeAllCommands();
}

void Editor::undoCommandFromCurrentSession()
{
	checkForActiveSession();

	this->sessions[indexOfCurrentSession].undoCommand();
}

void Editor::switchSessions(int newId)
{
	try
	{
		setIndexOfCurrentSession(newId);
		std::cout << Constants::SWITCH_MESSAGE << newId << std::endl;
	}
	catch (const std::invalid_argument&)
	{
		std::cout << Constants::INVALID_SWITCH_MESSAGE << std::endl;
	}
}

void Editor::addGrayscaleCommandToCurrentSession() 
{
	checkForActiveSession();

	GrayscaleCommand* cmd = new GrayscaleCommand();

	this->sessions[indexOfCurrentSession].commands.addCommand(cmd);
}


void Editor::addMonochromeCommandToCurrentSession() 
{
	checkForActiveSession();

	MonochromeCommand* cmd = new MonochromeCommand();

	this->sessions[indexOfCurrentSession].commands.addCommand(cmd);
}

void Editor::addNegativeCommandToCurrentSession() 
{
	checkForActiveSession();

	NegativeCommand* cmd = new NegativeCommand();

	this->sessions[indexOfCurrentSession].commands.addCommand(cmd);
}

void Editor::addRotateCommand(const char* direction) 
{
	checkForActiveSession();

	if (std::strcmp(direction, Constants::LEFT_COMMAND) == 0)
	{
		RotateCommand* cmd = new RotateCommand(Direction::Left);
		this->sessions[indexOfCurrentSession].commands.addCommand(cmd);
	}
	else if (std::strcmp(direction, Constants::RIGHT_COMMAND) == 0)
	{
		RotateCommand* cmd = new RotateCommand(Direction::Right);
		this->sessions[indexOfCurrentSession].commands.addCommand(cmd);
	}
	else
	{
		//TODO
		throw std::exception();
	}
}

void Editor::addAddCommand(const char* fileName)
{
	checkForActiveSession();

	AddCommand* cmd = new AddCommand(fileName);

	this->sessions[indexOfCurrentSession].commands.addCommand(cmd);
}

void Editor::addCollageCommand(const char* direction, const char* firstFile, const char* secondFile, const char* outImage)
{
	checkForActiveSession();

	if (std::strcmp(direction, Constants::HORIZONTAL_COMMAND) == 0)
	{
		CollageCommand* cmd = new CollageCommand(Direction::Horizontal, firstFile, secondFile, outImage);

		this->sessions[indexOfCurrentSession].commands.addCommand(cmd);
	}
	else if (std::strcmp(direction, Constants::VERTICAL_COMMAND) == 0)
	{
		CollageCommand* cmd = new CollageCommand(Direction::Vertical, firstFile, secondFile, outImage);

		this->sessions[indexOfCurrentSession].commands.addCommand(cmd);
	}
}

void Editor::load() 
{
	unsigned newIndex = this->sessions.getSize();
	Session session(newIndex);

	// Add session
	sessions.pushBack(session);
	setIndexOfCurrentSession(newIndex);
}

void Editor::currentSessionInfo() const 
{
	checkForActiveSession();

	this->sessions[indexOfCurrentSession].info();
}

void Editor::closeCurrentSession()
{
	checkForActiveSession();

	this->indexOfCurrentSession = -1;
	std::cout << Constants::CLOSE_SESSION_MESSAGE << std::endl;
}

void Editor::help() const 
{

}
