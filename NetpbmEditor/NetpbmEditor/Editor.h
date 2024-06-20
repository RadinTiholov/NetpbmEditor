#pragma once
#include "Vector.hpp"
#include "Session.h"
#include "RasterFile.h"
#include "FileFactory.h"

class Editor
{
private:
	Vector<Session> sessions;
	unsigned indexOfCurrentSession = 0;

	void setIndexOfCurrentSession(int newIndex);
	void serializeFile(const RasterFile*) const;
public:
	void serializeAllFilesInCurrentSession() const;
	void saveAs(const char* newFileName) const;
	void load(const char* fileName);
	void addToCurrentSession(const char* fileName);
	int findFileIndexInCurrentSessionByName(const char* fileName) const;
	void collage(const Direction& direction, int firstIndex, int secondIndex, const char* outFileName);
	void close(unsigned sessionId);
	void switchSession(unsigned sessionID);
	void help() const;
	void exit() const;
	//TODO : undo just remove the last command
	friend class GrayscaleCommand;
	friend class MonochromeCommand;
	friend class NegativeCommand;
	friend class RotateCommand;
	friend class AddCommand;
	friend class CollageCommand;
	friend class SwitchCommand;
};

