#include "CommandContainer.h"
#include <iostream>

CommandContainer::CommandContainer() 
{
	capacity = 8;
	data = new Command * [capacity] { nullptr };
	size = 0;
}

CommandContainer::CommandContainer(const CommandContainer& other) 
{
	copyFrom(other);
}
CommandContainer::CommandContainer(CommandContainer&& other) noexcept 
{
	moveFrom(std::move(other));
}

CommandContainer& CommandContainer::operator=(const CommandContainer& other) 
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

CommandContainer& CommandContainer::operator=(CommandContainer&& other) noexcept 
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

CommandContainer::~CommandContainer() 
{
	free();
}

void CommandContainer::addCommand(Command* command)
{
	if (size == capacity)
		resize(capacity * 2);
	data[size++] = command;
	command = nullptr;
}

void CommandContainer::addCommand(const Command& shape)
{
	Command* cloned = shape.clone();
	addCommand(cloned);
}

const Command* CommandContainer::operator[](unsigned index) const 
{
	return this->data[index];
}

Command* CommandContainer::operator[](unsigned index)
{
	return this->data[index];
}

unsigned CommandContainer::getSize() const 
{
	return this->size;
}

void CommandContainer::free() 
{
	for (int i = 0; i < size; i++)
		delete data[i];
	delete[] data;
}

void CommandContainer::copyFrom(const CommandContainer& other) 
{
	data = new Command * [other.capacity];

	for (int i = 0; i < other.size; i++)
		data[i] = other.data[i]->clone();

	size = other.size;
	capacity = other.capacity;
}

void CommandContainer::moveFrom(CommandContainer&& other) 
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	capacity = other.capacity;

	other.size = other.capacity = 0;
}

void CommandContainer::resize(size_t newCap) 
{
	Command** newData = new Command * [newCap];
	for (int i = 0; i < size; i++)
		newData[i] = data[i];
	delete[] data;
	data = newData;
	capacity = newCap;
}