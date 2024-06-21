#include "AddCommand.h"
#include "Session.h"

AddCommand::AddCommand(const char* fileName) 
{
	this->fileName = fileName;
}

void AddCommand::execute(Session& session)
{
	session.createFile(this->fileName.c_str());
}

Command* AddCommand::clone() const 
{
	return new AddCommand(*this);
}