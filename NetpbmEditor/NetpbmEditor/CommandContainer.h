#pragma once
#include "Command.h"

class CommandContainer
{
public:
	CommandContainer();
	CommandContainer(const CommandContainer& other);
	CommandContainer(CommandContainer&& other) noexcept;
	CommandContainer& operator=(const CommandContainer& other);
	CommandContainer& operator=(CommandContainer&& other) noexcept;
	~CommandContainer();

	void addCommand(Command* shape); //will take the ownership of the object  
	void addCommand(const Command& shape);

	void removeLast();
	void removeAt(int index);

	const Command* operator[](unsigned) const;
	Command* operator[](unsigned);
	unsigned getSize() const;
private:
	void free();
	void copyFrom(const CommandContainer& other);
	void moveFrom(CommandContainer&& other);

	void resize(size_t newCap);

	Command** data = nullptr;
	size_t capacity = 0;
	size_t size = 0;
};

