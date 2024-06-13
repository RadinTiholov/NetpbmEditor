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

            LoadCommand* cmd = new LoadCommand(fileName);

            commands.addCommand(cmd);
        }
        else if (std::strcmp(command, Constants::SAVE_COMMAND) == 0)
        {
            this->executeCommands();
            this->editor.serializeAllFilesInCurrentSession();
            // TODO: Remove the executed ones
        }
        else if(std::strcmp(command, Constants::GRAYSCALE_COMMAND) == 0)
        {
            GrayscaleCommand* cmd = new GrayscaleCommand();

            commands.addCommand(cmd);
        }
        else if (std::strcmp(command, Constants::MONOCHROME_COMMAND) == 0)
        {
            MonochromeCommand* cmd = new MonochromeCommand();

            commands.addCommand(cmd);
        }
        else if (std::strcmp(command, Constants::NEGATIVE_COMMAND) == 0)
        {
            NegativeCommand* cmd = new NegativeCommand();

            commands.addCommand(cmd);
        }
        else if (std::strcmp(command, Constants::ROTATE_COMMAND) == 0)
        {
            char direction[Constants::BASIC_BUFFER_SIZE];
            ss >> direction;

            if (std::strcmp(direction, Constants::LEFT_COMMAND) == 0)
            {
                RotateCommand* cmd = new RotateCommand(Direction::Left);
                commands.addCommand(cmd);
            }
            else if (std::strcmp(direction, Constants::RIGHT_COMMAND) == 0)
            {
                RotateCommand* cmd = new RotateCommand(Direction::Right);
                commands.addCommand(cmd);
            }
            else 
            {
                //TODO
                throw std::exception();
            }
        }
        else if (std::strcmp(command, Constants::ADD_COMMAND) == 0) 
        {
            char fileName[Constants::BASIC_BUFFER_SIZE];
            ss >> fileName;

            AddCommand* cmd = new AddCommand(fileName);

            commands.addCommand(cmd);
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

