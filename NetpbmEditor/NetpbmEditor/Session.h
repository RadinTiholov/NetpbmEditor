#pragma once
#include "RasterFileContainer.h"
#include "Direction.h"
#include "CommandContainer.h"
#include "Constants.h"
#include "UndoableCommand.h"
#include "FileFactory.h"

class Session
{
public:
	Session() = default;
	Session(unsigned id);
	unsigned getId() const;
	void addFile(RasterFile* file);
	void createFile(const char* createFile);
	void grayScale();
	void monochrome();
	void negative();
	void info() const;
	void rotate(const Direction& direction);
	void serializeAllFiles() const;
	void executeAllCommands();
	void removeAllCommands();
	void undoCommand();
	RasterFile* collage(const Direction& direction, int indexOfFirst, int indexOfSecond, const char* outFileName);

	friend class Editor;
	friend class GrayscaleCommand;
	friend class MonochromeCommand;
	friend class NegativeCommand;
	friend class RotateCommand;
	friend class AddCommand;
	friend class CollageCommand;
	friend class SwitchCommand;
private:
	unsigned _id = 0;
	RasterFileContainer files;
	CommandContainer commands;

	void serializeFile(const RasterFile*) const;
	int findFileIndexByName(const char* fileName) const;
};

