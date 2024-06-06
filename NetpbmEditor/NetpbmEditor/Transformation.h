#pragma once

class Transformation
{
public:
	virtual Transformation* clone() const = 0;
};