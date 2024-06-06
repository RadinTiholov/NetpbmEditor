#include "LoadCommand.h"

void LoadCommand::execute(Editor& editor)
{
	editor.load(this->fileName.c_str());
};

Command* LoadCommand::clone() const
{
	return new LoadCommand(*this);
};

LoadCommand::LoadCommand(const char* fileName) : fileName(fileName) {}