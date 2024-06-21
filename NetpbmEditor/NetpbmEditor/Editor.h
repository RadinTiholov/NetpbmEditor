#pragma once
#include "Vector.hpp"
#include "Session.h"
#include "CommandContainer.h"
#include "GrayscaleCommand.h"
#include "MonochromeCommand.h"
#include "NegativeCommand.h"
#include "RotateCommand.h"
#include "AddCommand.h"
#include "CollageCommand.h"
#include "Constants.h"
#include "Direction.h"

class Editor
{
private:
	Vector<Session> sessions;
	unsigned indexOfCurrentSession = 0;

	void setIndexOfCurrentSession(int newIndex);
public:
	void saveAs(const char* newFileName);
	void save();
	void load(const char* fileName);
	void undoCommandFromCurrentSession();
	void switchSessions(int newId);
	void addGrayscaleCommandToCurrentSession();
	void addMonochromeCommandToCurrentSession();
	void addNegativeCommandToCurrentSession();
	void addRotateCommand(const char* direction);
	void addAddCommand(const char* fileName);
	void addCollageCommand(const char* direction, const char* firstFile, const char* secondFile, const char* outImage);
	void currentSessionInfo() const;
	void close(unsigned sessionId);
	void help() const;
	void exit() const;
};

