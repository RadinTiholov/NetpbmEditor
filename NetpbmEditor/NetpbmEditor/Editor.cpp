#include "Editor.h"

void Editor::serializeAllFilesInCurrentSession() const
{
	for (size_t i = 0; i < this->sessions[indexOfCurrentSession].files.getSize(); i++)
	{
		serializeFile(this->sessions[indexOfCurrentSession].files[i]);
	}
}

void Editor::serializeFile(const RasterFile* file) const
{
	file->serialize();
}

void Editor::saveAs(const char* newFileName) const
{

}

void Editor::load(const char* fileName) 
{
	// TODO: Test this if works
	unsigned newIndex = this->sessions.getSize();
	this->indexOfCurrentSession = newIndex;
	Session session(newIndex);

	// Load image
	RasterFile* createdImage = FileFactory::createFile(fileName);
	session.addFile(createdImage);

	// Add session
	sessions.pushBack(session);
}
void Editor::close(unsigned sessionId) 
{

}
void Editor::switchSession(unsigned sessionID) 
{

}
void Editor::help() const 
{

}
void Editor::exit() const 
{

}
