#include "AddCommand.h"

AddCommand::AddCommand(const char* fileName) 
{
	this->fileName = fileName;
}

void AddCommand::execute(Editor& editor) 
{
	editor.addToCurrentSession(this->fileName.c_str());
}

Command* AddCommand::clone() const 
{
	return new AddCommand(*this);
}