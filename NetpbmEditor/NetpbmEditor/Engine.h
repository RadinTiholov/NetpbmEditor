#pragma once
#include "Editor.h"
#include "CommandContainer.h"
#include "GrayscaleCommand.h"
#include "MonochromeCommand.h"
#include "NegativeCommand.h"
#include "LoadCommand.h"
#include "RotateCommand.h"
#include "AddCommand.h"
#include "CollageCommand.h"
#include "Constants.h"
#include "Direction.h"
#include "SwitchCommand.h"
#include <sstream>

class Engine
{
public:
	void start(); // parse commands from the console
private:
	Editor editor;
	CommandContainer commands;

	void parseCommandsFrom(std::istream& ifs);
	void executeCommands();
	void removeCommands();
};

