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

void Editor::setIndexOfCurrentSession(int newIndex) 
{
	if (newIndex < 0 || newIndex >= this->sessions.getSize())
	{
		throw std::invalid_argument(Constants::INVALID_INDEX_ERROR_MESSAGE);
	}
	this->indexOfCurrentSession = newIndex;
}

void Editor::saveAs(const char* newFileName) const
{

}

void Editor::load(const char* fileName) 
{
	// TODO: Test this if works
	unsigned newIndex = this->sessions.getSize();
	Session session(newIndex);

	// Load image
	RasterFile* createdImage = FileFactory::createFile(fileName);
	session.addFile(createdImage);

	// Add session
	sessions.pushBack(session);
	setIndexOfCurrentSession(newIndex);
}

void Editor::addToCurrentSession(const char* fileName) 
{
	RasterFile* createdImage = FileFactory::createFile(fileName);
	this->sessions[this->indexOfCurrentSession].addFile(createdImage);
}

int Editor::findFileIndexInCurrentSessionByName(const char* fileName) const 
{
	for (size_t i = 0; i < sessions[indexOfCurrentSession].files.getSize(); i++)
	{
		if (std::strcmp(fileName, sessions[indexOfCurrentSession].files[i]->getFileName()) == 0)
		{
			return i;
		}
	}
	return -1;
}

void Editor::collage(const Direction& direction, int firstIndex, int secondIndex, const char* outFileName) 
{
	RasterFile* file = this->sessions[this->indexOfCurrentSession].collage(direction, firstIndex, secondIndex, outFileName);

	this->sessions[this->indexOfCurrentSession].addFile(file);
}

void Editor::currentSessionInfo() const 
{
	sessions[indexOfCurrentSession].info();
}

void Editor::close(unsigned sessionId) 
{

}

void Editor::help() const 
{

}
void Editor::exit() const 
{

}
