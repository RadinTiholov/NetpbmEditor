#include "Engine.h"

void Engine::start()
{
    parseCommandsFrom(std::cin);
}

void Engine::parseCommandsFrom(std::istream& ifs) 
{
    while (true)
    {
        char line[Constants::BASIC_BUFFER_SIZE];
        ifs.getline(line, Constants::BASIC_BUFFER_SIZE);
        std::stringstream ss(line);
        char command[Constants::BASIC_BUFFER_SIZE];
        ss >> command;

        //TODO: Add all commands
        if (std::strcmp(command, Constants::LOAD_COMMAND) == 0)
        {
            char fileName[Constants::BASIC_BUFFER_SIZE];
            ss >> fileName;

            LoadCommand* cmd3 = new LoadCommand(fileName);

            commands.addCommand(cmd3);
        }
        else if (std::strcmp(command, Constants::SAVE_COMMAND) == 0)
        {
            this->executeCommands();
            this->editor.serializeAllFilesInCurrentSession();
            // TODO: Remove the executed ones
        }
    }
}

void Engine::executeCommands()
{
    // Here we execute the commands consequentialy
    for (size_t i = 0; i < this->commands.getSize(); i++)
    {
        this->commands[i]->execute(this->editor);
    }
}

