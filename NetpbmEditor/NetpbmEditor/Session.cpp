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
		if (!this->files[i]->isGrayscale())
		{
			this->files[i]->grayscale();
		}
	}
}

void Session::monochrome() 
{
	for (size_t i = 0; i < this->files.getSize(); i++)
	{
		if (!this->files[i]->isMonochrome())
		{
			this->files[i]->monochrome();
		}
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

void Session::info()
{
	std::cout << "Information about session with ID: " <<  this->_id << std::endl;
	std::cout << "Name of images in the session: ";
	for (int i = 0; i < this->commands.getSize(); i++)
	{
		AddCommand* cmd = dynamic_cast<AddCommand*>(this->commands[i]);
		if (cmd != nullptr)
		{
			std::cout << cmd->getFileName() << ' ';
		}
	}
	std::cout << std::endl << "Pending transformations: ";
	for (int i = 0; i < this->commands.getSize(); i++)
	{
		AddCommand* cmd = dynamic_cast<AddCommand*>(this->commands[i]);
		if (cmd == nullptr)
		{
			std::cout << this->commands[i]->name() << ' ';
		}
	}
	std::cout << std::endl;
}

void Session::saveAsFirstFile(const char* fileName) 
{
	// Create mock session
	Session mockSession;
	//Find the first add command
	for (size_t i = 0; i < this->commands.getSize(); i++)
	{
		AddCommand* cmd = dynamic_cast<AddCommand*>(this->commands[i]);
		if (cmd != nullptr)
		{
			cmd->execute(mockSession);
			break;
		}
	}

	//Change the name of the file
	mockSession.files[0]->setFileName(fileName);

	//Remove all add commands
	CommandContainer commandsWithoutAdd;
	for (size_t i = 0; i < this->commands.getSize(); i++)
	{
		AddCommand* cmd = dynamic_cast<AddCommand*>(this->commands[i]);
		if (cmd == nullptr)
		{
			commandsWithoutAdd.addCommand(this->commands[i]);
		}
	}
	mockSession.commands = commandsWithoutAdd;

	// Execute all transformations on the file and save
	mockSession.executeAllCommands();
	mockSession.serializeAllFiles();
}