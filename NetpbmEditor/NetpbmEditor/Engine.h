#pragma once
#include "Editor.h"
#include "CommandContainer.h"
#include "GrayscaleCommand.h"
#include "MonochromeCommand.h"
#include "LoadCommand.h"

class Engine
{
public:
	void start(); // parse commands from the console
private:
	Editor editor;
	CommandContainer commands;

	void saveCommand();
};

