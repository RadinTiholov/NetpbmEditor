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
public:
	void save() const;
	void saveAs(const char* newFileName) const;
	void load(const char* fileName);
	void close(unsigned sessionId);
	void switchSession(unsigned sessionID);
	void help() const;
	void exit() const;
};

