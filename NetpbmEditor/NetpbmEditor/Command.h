#pragma once
#include "Direction.h"
#include "MyString.h"

class Session;

class Command 
{
public:
	virtual void execute(Session& session) = 0;

	virtual Command* clone() const = 0;
	virtual ~Command() = default;
};