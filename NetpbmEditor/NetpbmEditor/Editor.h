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

	void serializeFile(const RasterFile*) const;
public:
	void serializeAllFilesInCurrentSession() const;
	void saveAs(const char* newFileName) const;
	void load(const char* fileName);
	void close(unsigned sessionId);
	void switchSession(unsigned sessionID);
	void help() const;
	void exit() const;
	//TODO : undo just remove the last command
	friend class GrayscaleCommand;
	friend class MonochromeCommand;
};

