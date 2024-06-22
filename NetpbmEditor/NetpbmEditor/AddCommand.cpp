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

const char* AddCommand::getFileName() const 
{
	return this->fileName.c_str();
}

const char* AddCommand::name() 
{
	return Constants::ADD_COMMAND;
}