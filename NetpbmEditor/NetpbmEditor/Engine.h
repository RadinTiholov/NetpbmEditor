#pragma once
#include "Editor.h"
#include "CommandContainer.h"
#include "GrayscaleCommand.h"
#include "MonochromeCommand.h"
#include "NegativeCommand.h"
#include "LoadCommand.h"
#include "Constants.h"
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
};

