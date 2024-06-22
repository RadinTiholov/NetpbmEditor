#include "Session.h"

unsigned Session::getId() const 
{
	return this->_id;
}

Session::Session(unsigned id) 
{
	this->_id = id;
}

void Session::addFile(RasterFile* file) 
{
	this->files.addFile(file);
}

void Session::createFile(const char* fileName)
{
	RasterFile* createdImage = FileFactory::createFile(fileName);
	addFile(createdImage);
}

RasterFile* Session::collage(const Direction& direction, int indexOfFirst, int indexOfSecond, const char* outFileName) 
{
	return this->files[indexOfFirst]->collageWith(direction, this->files[indexOfSecond], outFileName);
}

void Session::grayScale() 
{
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		this->files[i]->grayscale();
	}
}

void Session::monochrome() 
{
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		this->files[i]->monochrome();
	}
}

void Session::negative() 
{
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		this->files[i]->negative();
	}
}

void Session::rotate(const Direction& direction)
{
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		this->files[i]->rotate(direction);
	}
}


void Session::serializeAllFiles() const 
{
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		serializeFile(this->files[i]);
	}
}

void Session::serializeFile(const RasterFile* file) const
{
	file->serialize();
}

void Session::executeAllCommands() 
{
	for (size_t i = 0; i < this->commands.getSize(); i++)
	{
		this->commands[i]->execute(*this);
	}
}

void Session::removeAllCommands() 
{
	int size = this->commands.getSize();
	for (size_t i = 0; i < size; i++)
	{
		this->commands.removeLast();
	}
}

void Session::undoCommand() 
{
	for (int i = this->commands.getSize() - 1; i >= 0; i--)
	{
		UndoableCommand* cmd = dynamic_cast<UndoableCommand*>(this->commands[i]);
		if (cmd != nullptr)
		{
			this->commands.removeAt(i);
			return;
		}
	}
	std::cout << Constants::UNDOABLE_MESSAGE << std::endl;
}

int Session::findFileIndexByName(const char* fileName) const 
{
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		if (std::strcmp(fileName, this->files[i]->getFileName()) == 0)
		{
			return i;
		}
	}
	return -1;
}

void Session::info() const 
{
	std::cout << "Information about session with id: " + this->_id << std::endl;
	std::cout << "Name of images in the session: ";
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		std::cout << this->files[i]->getFileName();
	}
	std::cout << std::endl;
}
