#include "Editor.h"

void Editor::save() const
{

}
void Editor::saveAs(const char* newFileName) const
{

}
void Editor::load(const char* fileName) 
{
	unsigned newIndex = this->sessions.getSize() + 1;
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
