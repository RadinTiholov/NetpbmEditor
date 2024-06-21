#pragma once
#include "Editor.h"
#include <sstream>

class Engine
{
public:
	void start(); // parse commands from the console
private:
	Editor editor;

	void parseCommandsFrom(std::istream& ifs);
};

