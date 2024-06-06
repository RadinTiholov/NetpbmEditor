#pragma once
#include "Editor.h"

class Command 
{
public:
	virtual void execute(Editor& editor) = 0;

	virtual Command* clone() const = 0;
	virtual ~Command() = default;
};